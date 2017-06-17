#include "graphwidget.h"
#include "gate.h"
#include "clock.h"
#include "userio.h"
#include "numericio.h"
#include "multiplexer.h"
#include "flipflop.h"
#include "counter.h"
#include "pin.h"
#include "wire.h"
#include "commands.h"
#include "widget.h"
#include "ui_widget.h"

Widget *Widget::instance=0;

Widget::Widget(QWidget *parent)
    : QWidget(parent),ui(new Ui::Widget)
{
    ui->setupUi(this);
    initialize();

    undoStack = new QUndoStack(this);
    createActions();
    createMenus();
    createToolBar();
    setCurrentFile("");
}

Widget::~Widget()
{
    delete ui;

    delete boardGraph;
    delete componentsGraph;
}

Widget *Widget::simulator()
{
    if(instance==0)
        instance=new Widget();
    return instance;
}

graphWidget *Widget::BoardGraph()
{
    return boardGraph;
}

graphWidget *Widget::ComponentsGraph()
{
    return componentsGraph;
}

void Widget::showDelay(int delay)
{
    ui->Delay->setNum(delay);
}

void Widget::itemMoved(Gate *movedGate, const QPointF &Position)
{
    lastmovecommand=new MoveCommand(movedGate,Position);
    undoStack->push(lastmovecommand);
}

void Widget::itemAdded(Gate *addedGate)
{
    undoStack->push(new AddCommand(addedGate));
}

void Widget::itemAdded(Clock *addedGate)
{
    undoStack->push(new AddCommand(addedGate));
}

void Widget::itemAdded(UserIO *addedGate)
{
    undoStack->push(new AddCommand(addedGate));
}

void Widget::itemAdded(NumericIO *addedGate)
{
    undoStack->push(new AddCommand(addedGate));
}

void Widget::itemAdded(Multiplexer *addedGate)
{
    undoStack->push(new AddCommand(addedGate));
}

void Widget::itemAdded(Flipflop *addedGate)
{
    undoStack->push(new AddCommand(addedGate));
}

void Widget::itemAdded(Counter *addedGate)
{
    undoStack->push(new AddCommand(addedGate));
}

MoveCommand *Widget::lastMoveCommand()
{
    return lastmovecommand;
}

void Widget::initialize()
{
    ui->Speed->setMinimum(1);
    ui->Speed->setMaximum(1000);

    boardGraph=new graphWidget(board);
    componentsGraph=new graphWidget(components);

    ui->board_scrollArea->setWidget(boardGraph);
    ui->components_scrollArea->setWidget(componentsGraph);

    ui->board_scrollArea->setStyleSheet("border-width: 1px;"
                                             "border-radius: 1px;"
                                             "border-style: inset;"
                                             "border-color: gold;");
    ui->components_scrollArea->setStyleSheet("border-width: 1px;"
                                             "border-radius: 1px;"
                                             "border-style: inset;"
                                             "border-color: gold;");
}

void Widget::on_component_Type_currentIndexChanged(int index)
{
    switch(index)
    {
    case 0:
        componentsGraph->basicGates();
        break;

    case 1:
        componentsGraph->compoundGates();
        break;

    case 2:
        componentsGraph->ioGates();
        break;

    case 3:
        componentsGraph->additionalGates();
        break;

    default:
        componentsGraph->basicGates();
        break;
    }
}

void Widget::on_Speed_sliderMoved(int position)
{
    boardGraph->resetTimer(position);
}

void Widget::newFile()
{
    if (maybeSave())
    {
        delete boardGraph;
        delete componentsGraph;
        boardGraph = new graphWidget(board);
        componentsGraph = new graphWidget(components);
        ui->board_scrollArea->setWidget(boardGraph);
        ui->components_scrollArea->setWidget(componentsGraph);
        ui->Speed->setValue(1);
        ui->Delay->setNum(1);
        ui->component_Type->setCurrentIndex(0);

        setCurrentFile("");
    }
}

bool Widget::save()
{
    if (curFile.isEmpty())
    {
        return saveAs();
    }
    else
    {
        return saveFile(curFile);
    }
}

bool Widget::saveAs()
{
    QString fileName = QFileDialog::getSaveFileName(this);
    if (fileName.isEmpty())
        return false;

    return saveFile(fileName);
}

void Widget::load()
{
    QString fileName = QFileDialog::getOpenFileName(this);
    if (!fileName.isEmpty())
        loadFile(fileName);
}

void Widget::about()
{
    QMessageBox::about(this, tr("About Simulator"),
             tr("This Application is a simple Logic Simulator, "
                "based on QT Framework. \n"
                "Developed by Saeed Ghodsi"));
}

void Widget::createActions()
{
    newAct = new QAction(QIcon("C:/Images/NEWICON.png"), tr("&New"), this);
    newAct->setShortcuts(QKeySequence::New);
    newAct->setStatusTip(tr("Create a new file"));
    connect(newAct, SIGNAL(triggered()), this, SLOT(newFile()));

    saveAct = new QAction(QIcon("C:/Images/SAVEICON.png"), tr("&Save"), this);
    saveAct->setShortcuts(QKeySequence::Save);
    saveAct->setStatusTip(tr("Save the document to disk"));
    connect(saveAct, SIGNAL(triggered()), this, SLOT(save()));

    saveAsAct = new QAction(tr("Save &As..."), this);
    saveAsAct->setShortcuts(QKeySequence::SaveAs);
    saveAsAct->setStatusTip(tr("Save the document under a new name"));
    connect(saveAsAct, SIGNAL(triggered()), this, SLOT(saveAs()));

    loadAct = new QAction(QIcon("C:/Images/LOADICON.png"), tr("&Load..."), this);
    loadAct->setShortcuts(QKeySequence::Open);
    loadAct->setStatusTip(tr("Load an existing file"));
    connect(loadAct, SIGNAL(triggered()), this, SLOT(load()));

    undoAct = undoStack->createUndoAction(this, tr("&Undo"));
    undoAct->setShortcuts(QKeySequence::Undo);
    undoAct->setStatusTip(tr("Undo last act"));

    redoAct = undoStack->createRedoAction(this, tr("&Redo"));
    redoAct->setShortcuts(QKeySequence::Redo);
    redoAct->setStatusTip(tr("Redo last act"));

    exitAct = new QAction(tr("E&xit"), this);
    exitAct->setShortcuts(QKeySequence::Quit);
    exitAct->setStatusTip(tr("Exit the application"));
    connect(exitAct, SIGNAL(triggered()), this, SLOT(close()));

    aboutAct = new QAction(tr("&About"), this);
    aboutAct->setStatusTip(tr("Show the application's About box"));
    connect(aboutAct, SIGNAL(triggered()), this, SLOT(about()));

    aboutQtAct = new QAction(tr("About &Qt"), this);
    aboutQtAct->setStatusTip(tr("Show the Qt library's About box"));
    connect(aboutQtAct, SIGNAL(triggered()), qApp, SLOT(aboutQt()));
}

void Widget::createMenus()
{
    simulatorMenuBar = new QMenuBar(this);
    fileMenu = simulatorMenuBar->addMenu(tr("&File"));
    fileMenu->addAction(newAct);
    fileMenu->addAction(saveAct);
    fileMenu->addAction(saveAsAct);
    fileMenu->addAction(loadAct);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAct);

    editMenu = simulatorMenuBar->addMenu(tr("&Edit"));
    editMenu->addAction(undoAct);
    editMenu->addAction(redoAct);

    helpMenu = simulatorMenuBar->addMenu(tr("&Help"));
    helpMenu->addAction(aboutAct);
    helpMenu->addAction(aboutQtAct);
}

void Widget::createToolBar()
{
    fileToolBar = new QToolBar(tr("File"),this);
    fileToolBar->addAction(newAct);
    fileToolBar->addAction(saveAct);
    fileToolBar->addAction(loadAct);
    fileToolBar->move(QPoint(0,25));
    fileToolBar->show();
}

void Widget::readSettings()
{
    QSettings settings("SUT", "Logic Simulator");
    QPoint pos = settings.value("pos", QPoint(200, 200)).toPoint();
    QSize size = settings.value("size", QSize(400, 400)).toSize();
    resize(size);
    move(pos);
}

void Widget::writeSettings()
{
    QSettings settings("SUT", "Logic Simulator");
    settings.setValue("pos", pos());
    settings.setValue("size", size());
}

bool Widget::maybeSave()
{
    QMessageBox::StandardButton ret;
    ret = QMessageBox::warning(this, tr("Simulator"),
                 tr("Do you want to save your changes?"),
                 QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);

    if (ret == QMessageBox::Yes)
        return save();

    if (ret == QMessageBox::Cancel)
        return false;

    return true;
}

bool Widget::saveFile(const QString &fileName)
{
    QFile file(fileName);
    if (!file.open(QFile::WriteOnly))
    {
        QMessageBox::warning(this, tr("Simulator"),
                             tr("Cannot write file %1:\n%2.")
                             .arg(fileName)
                             .arg(file.errorString()));
        return false;
    }

    QDataStream out(&file);

#ifndef QT_NO_CURSOR
    QApplication::setOverrideCursor(Qt::WaitCursor);
#endif

    out << ui->Speed->value();
    out << ui->Delay->text();
    out << ui->component_Type->currentIndex();

    out << boardGraph->getGates().count() << boardGraph->getClocks().count();
    out << boardGraph->getUserIOs().count() << boardGraph->getNumericIOs().count();
    out << boardGraph->getMultiplexers().count() << boardGraph->getFlipflops().count();
    out << boardGraph->getCounters().count() << boardGraph->getWires().count();
    foreach (Gate *gate, boardGraph->getGates())
    {
        out << gate->getGateType() << gate->getPos();
    }
    foreach (Clock *gate, boardGraph->getClocks())
    {
        out << gate->getPos() << gate->getPeriod();
    }
    foreach (UserIO *gate, boardGraph->getUserIOs())
    {
        out << gate->getGateType() << gate->getPos();
        out << gate->getState();
    }
    foreach (NumericIO *gate, boardGraph->getNumericIOs())
    {
        out << gate->getGateType() << gate->getPos();
        out << gate->getNumberOfBits() << gate->getDisplayValue() << gate->getBaseValue();
    }
    foreach (Multiplexer *gate, boardGraph->getMultiplexers())
    {
        out << gate->getPos() << gate->getNumberOfBits();
    }
    foreach (Flipflop *gate, boardGraph->getFlipflops())
    {
        out << gate->getPos();
    }
    foreach (Counter *gate, boardGraph->getCounters())
    {
        out << gate->getPos() << gate->getNumberOfBits() << gate->getDisplayValue();
    }
    foreach (Wire *wire, boardGraph->getWires())
    {
        out << wire->sourcePin()->parentGate()->getGateType();
        out << wire->sourcePin()->parentGate()->getGateIndex();
        out << wire->sourcePin()->getPinIndex();

        out << wire->destPin()->parentGate()->getGateType();
        out << wire->destPin()->parentGate()->getGateIndex();
        out << wire->destPin()->getPinIndex();
    }

#ifndef QT_NO_CURSOR
    QApplication::restoreOverrideCursor();
#endif

    setCurrentFile(fileName);
    writeSettings();
    return true;
}

void Widget::loadFile(const QString &fileName)
{
    QFile file(fileName);
    if (!file.open(QFile::ReadOnly))
    {
        QMessageBox::warning(this, tr("Simulator"),
                             tr("Cannot read file %1:\n%2.")
                             .arg(fileName)
                             .arg(file.errorString()));
        return;
    }

    QDataStream in(&file);

#ifndef QT_NO_CURSOR
    QApplication::setOverrideCursor(Qt::WaitCursor);
#endif

    delete boardGraph;
    delete componentsGraph;
    boardGraph = new graphWidget(board);
    componentsGraph = new graphWidget(components);
    ui->board_scrollArea->setWidget(boardGraph);
    ui->components_scrollArea->setWidget(componentsGraph);
    setCurrentFile("");
    int value;
    QString delay;
    int index;
    in >> value >> delay >> index;
    ui->Speed->setValue(value);
    ui->Delay->setText(delay);
    ui->component_Type->setCurrentIndex(index);
    on_Speed_sliderMoved(value);
    on_component_Type_currentIndexChanged(index);

    int gateCount,clockCount,userioCount,numericioCount,multiplexersCount,flipflopsCount,countersCount,wireCount;
    in >> gateCount >>clockCount >> userioCount >> numericioCount;
    in >> multiplexersCount >> flipflopsCount >> countersCount >> wireCount;
    for(int i=0;i<gateCount;i++)
    {
        int type;
        QPointF pos;
        in >> type >> pos;
        boardGraph->addGate(type,pos,false);
    }
    for(int i=0;i<clockCount;i++)
    {
        QPointF pos;
        int period;
        in >> pos >> period;
        boardGraph->addClock(pos,false,period);
    }
    for(int i=0;i<userioCount;i++)
    {
        int type;
        QPointF pos;
        bool state;
        in >> type >> pos >> state;
        boardGraph->addUserIO(type,pos,false,state);
    }
    for(int i=0;i<numericioCount;i++)
    {
        int type;
        QPointF pos;
        int numberofbits;
        int displayvalue;
        int basevalue;
        in >> type >> pos >> numberofbits >> displayvalue >> basevalue;
        boardGraph->addNumericIO(type,pos,true,false,numberofbits,displayvalue,basevalue);
    }
    for(int i=0;i<multiplexersCount;i++)
    {
        QPointF pos;
        int numberofbits;
        in >> pos >> numberofbits;
        boardGraph->addMultiplexer(pos,true,false,numberofbits);
    }
    for(int i=0;i<flipflopsCount;i++)
    {
        QPointF pos;
        in >> pos;
        boardGraph->addFlipflop(pos,false);
    }
    for(int i=0;i<countersCount;i++)
    {
        QPointF pos;
        int numberofbits;
        int number;
        in >> pos >> numberofbits >> number;
        boardGraph->addCounter(pos,true,false,numberofbits,number);
    }
    for(int i=0;i<wireCount;i++)
    {
        int sourceGateType,sourceGateIndex,sourcePinIndex;
        int destGateType,destGateIndex,destPinIndex;
        in >> sourceGateType >> sourceGateIndex >> sourcePinIndex;
        in >> destGateType >> destGateIndex >> destPinIndex;
        boardGraph->addWire(sourceGateType,sourceGateIndex,sourcePinIndex,destGateType,destGateIndex,destPinIndex);
    }


#ifndef QT_NO_CURSOR
    QApplication::restoreOverrideCursor();
#endif

    setCurrentFile(fileName);
    readSettings();
}

void Widget::setCurrentFile(const QString &fileName)
{
    curFile = fileName;

    QString shownName = curFile;
    if (curFile.isEmpty())
        shownName = "untitled";
    setWindowFilePath(shownName);
}

QString Widget::strippedName(const QString &fullFileName)
{
    return QFileInfo(fullFileName).fileName();
}

void Widget::closeEvent(QCloseEvent *event)
{
    if (maybeSave())
    {
        event->accept();
    }
    else
    {
        event->ignore();
    }
}
