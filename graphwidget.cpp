#include "widget.h"
#include "gate.h"
#include "clock.h"
#include "userio.h"
#include "numericio.h"
#include "multiplexer.h"
#include "flipflop.h"
#include "counter.h"
#include "wire.h"
#include "pin.h"
#include "graphwidget.h"

graphWidget::graphWidget(graphType type, QWidget *parent)
    : QGraphicsView(parent)
{
    graphScene = new QGraphicsScene(this);
    graphScene->setItemIndexMethod(QGraphicsScene::NoIndex);
    setScene(graphScene);
    setCacheMode(CacheBackground);
    setViewportUpdateMode(BoundingRectViewportUpdate);
    setRenderHint(QPainter::Antialiasing);
    setTransformationAnchor(AnchorUnderMouse);
    setCursor(Qt::OpenHandCursor);
    setAcceptDrops(true);
    wireDrawing=false;
    startPin = new Pin;

    movinggate = 0;

    timerID=startTimer(1);
    delay=1;

    switch(type)
    {
    case board:
        Board();
        break;

    case components:
        Components();
        break;

    default:
        break;
    }
}

graphWidget::~graphWidget()
{
    //didn't delete gates!!!
    delete graphScene;
}

void graphWidget::Board()
{
    //graphScene->setSceneRect( 0, 0, 500, 500);
    iscomponentswidget=false;
    scaleView(qreal(0.5));
}

void graphWidget::Components()
{
    iscomponentswidget=true;
    basicGates();
}

void graphWidget::basicGates()
{
    delete graphScene;
    graphScene = new QGraphicsScene(this);
    graphScene->setItemIndexMethod(QGraphicsScene::NoIndex);
    setScene(graphScene);

    BUFFER = new Gate(Buffer);
    NOT = new Gate(Not);
    AND = new Gate(And);
    OR = new Gate(Or);

    graphScene->addItem(BUFFER);
    graphScene->addItem(NOT);
    graphScene->addItem(AND);
    graphScene->addItem(OR);

    BUFFER->setPos(50, 50);
    NOT->setPos(50, 150);
    AND->setPos(50, 250);
    OR->setPos(50, 350);
}

void graphWidget::compoundGates()
{
    delete graphScene;
    graphScene = new QGraphicsScene(this);
    graphScene->setItemIndexMethod(QGraphicsScene::NoIndex);
    setScene(graphScene);

    NAND = new Gate(Nand);
    NOR = new Gate(Nor);
    XOR = new Gate(Xor);
    XNOR = new Gate(Xnor);

    graphScene->addItem(NAND);
    graphScene->addItem(NOR);
    graphScene->addItem(XOR);
    graphScene->addItem(XNOR);

    NAND->setPos(50, 50);
    NOR->setPos(50, 150);
    XOR->setPos(50, 250);
    XNOR->setPos(50, 350);
}

void graphWidget::ioGates()
{
    delete graphScene;
    graphScene = new QGraphicsScene(this);
    graphScene->setItemIndexMethod(QGraphicsScene::NoIndex);
    setScene(graphScene);

    CLOCK = new Clock(true);
    USERINPUT = new UserIO(UserInput);
    USEROUTPUT = new UserIO(UserOutput);
    NUMERICINPUT = new NumericIO(NumericInput);
    NUMERICOUTPUT = new NumericIO(NumericOutput);

    graphScene->addItem(CLOCK);
    graphScene->addItem(USERINPUT);
    graphScene->addItem(USEROUTPUT);
    graphScene->addItem(NUMERICINPUT);
    graphScene->addItem(NUMERICOUTPUT);

    CLOCK->setPos(50, 50);
    USERINPUT->setPos(50, 150);
    USEROUTPUT->setPos(50, 250);
    NUMERICINPUT->setPos(50, 350);
    NUMERICOUTPUT->setPos(50, 450);
}

void graphWidget::additionalGates()
{
    delete graphScene;
    graphScene = new QGraphicsScene(this);
    graphScene->setItemIndexMethod(QGraphicsScene::NoIndex);
    setScene(graphScene);

    MULTIPLEXER = new Multiplexer();
    FLIPFLOP = new Flipflop();
    COUNTER = new Counter();

    graphScene->addItem(MULTIPLEXER);
    graphScene->addItem(FLIPFLOP);
    graphScene->addItem(COUNTER);

    MULTIPLEXER->setPos(50, 50);
    FLIPFLOP->setPos(50, 150);
    COUNTER->setPos(50, 250);
}

void graphWidget::startDrawing(Pin *pin)
{
    startPin=pin;
    wireDrawing=true;
    startPin->select(true);
}

void graphWidget::finishDrawing(Pin *endPin)
{
    if(startPin->parentGate() != endPin->parentGate())
    {
        if((startPin->getPinType()==OutputPin && endPin->getPinType()==InputPin))
            if(endPin->connectedWires().isEmpty())
                addWire(startPin,endPin);

        if((startPin->getPinType()==InputPin && endPin->getPinType()==OutputPin))
            if(startPin->connectedWires().isEmpty())
                addWire(endPin,startPin);
    }
    wireDrawing=false;
    if(startPin != 0)
    {
        startPin->select(false);
        startPin=0;
    }
}

bool graphWidget::isDrawing()
{
    return wireDrawing;
}

void graphWidget::addItem(int type, QPointF pos)
{
    switch(type)
    {
    case 0:
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
    case 7:
        addGate(type,pos);
        break;

    case 8:
        addClock(pos);
        break;

    case 9:
    case 10:
        addUserIO(type,pos);
        break;

    case 11:
    case 12:
        addNumericIO(type,pos);
        break;

    case 13:
        addMultiplexer(pos);
        break;

    case 14:
        addFlipflop(pos);
        break;

    case 15:
        addCounter(pos);
        break;

    default:
        addGate(type,pos);
        break;
    }
}

Gate *graphWidget::addGate(int type, QPointF pos, bool isForUndo)
{
    Gate *newGate;
    newGate = new Gate(type);
    newGate->setGateIndex(gates.count());
    gates << newGate;
    graphScene->addItem(newGate);
    newGate->setPos(pos);
    newGate->show();
    if(isForUndo==false)
        Widget::simulator()->itemAdded(newGate);
    return newGate;
}

Clock *graphWidget::addClock(QPointF pos, bool isForUndo, int period)
{
    Clock *newGate;
    newGate = new Clock(false,period);
    newGate->setGateIndex(clocks.count());
    clocks << newGate;
    graphScene->addItem(newGate);
    newGate->setPos(pos);
    newGate->show();
    if(isForUndo==false)
        Widget::simulator()->itemAdded(newGate);
    return newGate;
}

UserIO *graphWidget::addUserIO(int type, QPointF pos, bool isForUndo, bool state)
{
    UserIO *newGate;
    newGate = new UserIO(type,state);
    newGate->setGateIndex(userios.count());
    userios << newGate;
    graphScene->addItem(newGate);
    newGate->setPos(pos);
    newGate->show();
    if(isForUndo==false)
        Widget::simulator()->itemAdded(newGate);
    return newGate;
}

NumericIO *graphWidget::addNumericIO(int type, QPointF pos, bool instantDraw, bool isForUndo, int bits, int value, int numbase)
{
    NumericIO *newGate;
    newGate = new NumericIO(type,instantDraw,bits,value,numbase);
    newGate->setGateIndex(numericios.count());
    numericios << newGate;
    graphScene->addItem(newGate);
    newGate->setPos(pos);
    newGate->show();
    if(isForUndo==false)
        Widget::simulator()->itemAdded(newGate);
    return newGate;
}

Multiplexer *graphWidget::addMultiplexer(QPointF pos, bool instantDraw, bool isForUndo, int bits)
{
    Multiplexer *newGate;
    newGate = new Multiplexer(instantDraw,bits);
    newGate->setGateIndex(multiplexers.count());
    multiplexers << newGate;
    graphScene->addItem(newGate);
    newGate->setPos(pos);
    newGate->show();
    if(isForUndo==false)
        Widget::simulator()->itemAdded(newGate);
    return newGate;
}

Flipflop *graphWidget::addFlipflop(QPointF pos, bool isForUndo)
{
    Flipflop *newGate;
    newGate = new Flipflop(false);
    newGate->setGateIndex(flipflops.count());
    flipflops << newGate;
    graphScene->addItem(newGate);
    newGate->setPos(pos);
    newGate->show();
    if(isForUndo==false)
        Widget::simulator()->itemAdded(newGate);
    return newGate;
}

Counter *graphWidget::addCounter(QPointF pos, bool instantDraw, bool isForUndo, int bits, int value)
{
    Counter *newGate;
    newGate = new Counter(instantDraw,bits,value);
    newGate->setGateIndex(counters.count());
    counters << newGate;
    graphScene->addItem(newGate);
    newGate->setPos(pos);
    newGate->show();
    if(isForUndo==false)
        Widget::simulator()->itemAdded(newGate);
    return newGate;
}

void graphWidget::deleteGate(Gate *gate)
{
    foreach (Pin *pin, gate->InputList())
    {
        foreach (Wire *wire, pin->connectedWires())
        {
            wire->sourcePin()->deleteWire(wire);
            wire->destPin()->deleteWire(wire);
            wires.removeOne(wire);
            graphScene->removeItem(wire);
        }
    }
    foreach (Pin *pin, gate->OutputList())
    {
        foreach (Wire *wire, pin->connectedWires())
        {
            wire->sourcePin()->deleteWire(wire);
            wire->destPin()->deleteWire(wire);
            wires.removeOne(wire);
            graphScene->removeItem(wire);
        }
    }
    gates.removeOne(gate);
    graphScene->removeItem(gate);
    delete gate;
}

void graphWidget::deleteClock(Clock *gate)
{
    foreach (Pin *pin, gate->OutputList())
    {
        foreach (Wire *wire, pin->connectedWires())
        {
            wire->sourcePin()->deleteWire(wire);
            wire->destPin()->deleteWire(wire);
            wires.removeOne(wire);
            graphScene->removeItem(wire);
        }
    }
    clocks.removeOne(gate);
    graphScene->removeItem(gate);
    delete gate;
}

void graphWidget::deleteUserIO(UserIO *gate)
{
    foreach (Pin *pin, gate->InputList())
    {
        foreach (Wire *wire, pin->connectedWires())
        {
            wire->sourcePin()->deleteWire(wire);
            wire->destPin()->deleteWire(wire);
            wires.removeOne(wire);
            graphScene->removeItem(wire);
        }
    }
    foreach (Pin *pin, gate->OutputList())
    {
        foreach (Wire *wire, pin->connectedWires())
        {
            wire->sourcePin()->deleteWire(wire);
            wire->destPin()->deleteWire(wire);
            wires.removeOne(wire);
            graphScene->removeItem(wire);
        }
    }
    userios.removeOne(gate);
    graphScene->removeItem(gate);
    delete gate;
}

void graphWidget::deleteNumericIO(NumericIO *gate)
{
    foreach (Pin *pin, gate->InputList())
    {
        foreach (Wire *wire, pin->connectedWires())
        {
            wire->sourcePin()->deleteWire(wire);
            wire->destPin()->deleteWire(wire);
            wires.removeOne(wire);
            graphScene->removeItem(wire);
        }
    }
    foreach (Pin *pin, gate->OutputList())
    {
        foreach (Wire *wire, pin->connectedWires())
        {
            wire->sourcePin()->deleteWire(wire);
            wire->destPin()->deleteWire(wire);
            wires.removeOne(wire);
            graphScene->removeItem(wire);
        }
    }
    numericios.removeOne(gate);
    graphScene->removeItem(gate);
    delete gate;
}

void graphWidget::deleteMultiplexer(Multiplexer *gate)
{
    foreach (Pin *pin, gate->InputList())
    {
        foreach (Wire *wire, pin->connectedWires())
        {
            wire->sourcePin()->deleteWire(wire);
            wire->destPin()->deleteWire(wire);
            wires.removeOne(wire);
            graphScene->removeItem(wire);
        }
    }
    foreach (Pin *pin, gate->OutputList())
    {
        foreach (Wire *wire, pin->connectedWires())
        {
            wire->sourcePin()->deleteWire(wire);
            wire->destPin()->deleteWire(wire);
            wires.removeOne(wire);
            graphScene->removeItem(wire);
        }
    }
    multiplexers.removeOne(gate);
    graphScene->removeItem(gate);
    delete gate;
}

void graphWidget::deleteFlipflop(Flipflop *gate)
{
    foreach (Pin *pin, gate->InputList())
    {
        foreach (Wire *wire, pin->connectedWires())
        {
            wire->sourcePin()->deleteWire(wire);
            wire->destPin()->deleteWire(wire);
            wires.removeOne(wire);
            graphScene->removeItem(wire);
        }
    }
    foreach (Pin *pin, gate->OutputList())
    {
        foreach (Wire *wire, pin->connectedWires())
        {
            wire->sourcePin()->deleteWire(wire);
            wire->destPin()->deleteWire(wire);
            wires.removeOne(wire);
            graphScene->removeItem(wire);
        }
    }
    flipflops.removeOne(gate);
    graphScene->removeItem(gate);
    delete gate;
}

void graphWidget::deleteCounter(Counter *gate)
{
    foreach (Pin *pin, gate->InputList())
    {
        foreach (Wire *wire, pin->connectedWires())
        {
            wire->sourcePin()->deleteWire(wire);
            wire->destPin()->deleteWire(wire);
            wires.removeOne(wire);
            graphScene->removeItem(wire);
        }
    }
    foreach (Pin *pin, gate->OutputList())
    {
        foreach (Wire *wire, pin->connectedWires())
        {
            wire->sourcePin()->deleteWire(wire);
            wire->destPin()->deleteWire(wire);
            wires.removeOne(wire);
            graphScene->removeItem(wire);
        }
    }
    counters.removeOne(gate);
    graphScene->removeItem(gate);
    delete gate;
}

void graphWidget::addWire(Pin *startPin, Pin *endPin)
{
    Wire *newWire=new Wire(startPin, endPin);
    wires << newWire;
    graphScene->addItem(newWire);
}

void graphWidget::addWire(int sourceGateType, int sourceGateIndex, int sourcePinIndex, int destGateType, int destGateIndex, int destPinIndex)
{
    Pin *sourcePin;
    Pin *destPin;
    switch(sourceGateType)
    {
    case 0:
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
    case 7:
        sourcePin=gates[sourceGateIndex]->OutputList()[sourcePinIndex];
        break;

    case 8:
        sourcePin=clocks[sourceGateIndex]->OutputList()[sourcePinIndex];
        break;

    case 9:
    case 10:
        sourcePin=userios[sourceGateIndex]->OutputList()[sourcePinIndex];
        break;

    case 11:
    case 12:
        sourcePin=numericios[sourceGateIndex]->OutputList()[sourcePinIndex];
        break;

    case 13:
        sourcePin=multiplexers[sourceGateIndex]->OutputList()[sourcePinIndex];
        break;

    case 14:
        sourcePin=flipflops[sourceGateIndex]->OutputList()[sourcePinIndex];
        break;

    case 15:
        sourcePin=counters[sourceGateIndex]->OutputList()[sourcePinIndex];
        break;

    default:
        break;
    }
    switch(destGateType)
    {
    case 0:
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
    case 7:
        destPin=gates[destGateIndex]->InputList()[destPinIndex];
        break;

    case 8:
        destPin=clocks[destGateIndex]->InputList()[destPinIndex];
        break;

    case 9:
    case 10:
        destPin=userios[destGateIndex]->InputList()[destPinIndex];
        break;

    case 11:
    case 12:
        destPin=numericios[destGateIndex]->InputList()[destPinIndex];
        break;

    case 13:
        destPin=multiplexers[destGateIndex]->InputList()[destPinIndex];
        break;

    case 14:
        destPin=flipflops[destGateIndex]->InputList()[destPinIndex];
        break;

    case 15:
        destPin=counters[destGateIndex]->InputList()[destPinIndex];
        break;

    default:
        break;
    }
    addWire(sourcePin,destPin);
}

void graphWidget::deleteWire(Wire *wire)
{
    wire->sourcePin()->deleteWire(wire);
    wire->destPin()->deleteWire(wire);
    wires.removeOne(wire);
    graphScene->removeItem(wire);
}

QGraphicsScene *graphWidget::scene()
{
    return graphScene;
}

void graphWidget::resetTimer(int position)
{
    killTimer(timerID);
    timerID=startTimer(position);

    delay=position;
    Widget::simulator()->showDelay(delay);
}

QList<Gate *> graphWidget::getGates()
{
    return gates;
}

QList<Clock *> graphWidget::getClocks()
{
    return clocks;
}

QList<UserIO *> graphWidget::getUserIOs()
{
    return userios;
}

QList<NumericIO *> graphWidget::getNumericIOs()
{
    return numericios;
}

QList<Multiplexer *> graphWidget::getMultiplexers()
{
    return multiplexers;
}

QList<Flipflop *> graphWidget::getFlipflops()
{
    return flipflops;
}

QList<Counter *> graphWidget::getCounters()
{
    return counters;
}

QList<Wire *> graphWidget::getWires()
{
    return wires;
}

void graphWidget::keyPressEvent(QKeyEvent *event)
{
    switch (event->key())
    {
    case Qt::Key_Plus:
        zoomIn();
        break;
    case Qt::Key_Minus:
        zoomOut();
        break;
    default:
        QGraphicsView::keyPressEvent(event);
    }
}

#ifndef QT_NO_WHEELEVENT
void graphWidget::wheelEvent(QWheelEvent *event)
{
    scaleView(pow((double)2, event->delta() / 240.0));
}

#endif

void graphWidget::scaleView(qreal scaleFactor)
{
    if(iscomponentswidget==true)
        return;

    qreal factor = transform().scale(scaleFactor, scaleFactor).mapRect(QRectF(0, 0, 1, 1)).width();
    if (factor < 0.1 || factor > 10)
        return;

    scale(scaleFactor, scaleFactor);
}

void graphWidget::zoomIn()
{
    scaleView(qreal(1.2));
}

void graphWidget::zoomOut()
{
    scaleView(1 / qreal(1.2));
}

void graphWidget::mousePressEvent(QMouseEvent *event)
{
    setCursor(Qt::ClosedHandCursor);

    if(iscomponentswidget==true)
    {
        if (!(event->buttons() & Qt::LeftButton))
                return;

        Gate *child = static_cast<Gate *>(itemAt(event->pos()));
        if (!child)
            return;

        Pin *childPin = static_cast<Pin *>(itemAt(event->pos()));
        if(childPin->getItemType()==pin)
            return;

        QPixmap pixmap = child->pixmap();

        QByteArray itemData;
        QDataStream dataStream(&itemData, QIODevice::WriteOnly);
        dataStream << child->getGateType() << QPoint(event->pos() - mapFromScene(child->pos().toPoint()));

        QMimeData *mimeData = new QMimeData;
        mimeData->setData("Gate", itemData);

        QDrag *drag = new QDrag(this);
        drag->setMimeData(mimeData);
        drag->setPixmap(pixmap);
        drag->setHotSpot(event->pos() - mapFromScene(child->pos().toPoint()));

        QPixmap tempPixmap = pixmap;
        QPainter painter;
        painter.begin(&tempPixmap);
        painter.fillRect(pixmap.rect(), QColor(127, 127, 127, 127));
        painter.end();
        child->setPixmap(tempPixmap);

        if (drag->exec(Qt::CopyAction | Qt::MoveAction, Qt::CopyAction) == Qt::MoveAction)
        {
            child->hide();
        }
        else
        {
            child->show();
            child->setPixmap(pixmap);
        }
    }
    else
    {
        if(!(event->buttons() & Qt::LeftButton))
        {
            if(event->buttons() & Qt::RightButton)
            {
                Gate *child = static_cast<Gate *>(itemAt(event->pos()));
                if (!child)
                    return;

                if(child->getItemType()!=gate)
                {
                    if(child->getItemType()!=wire)
                        return;
                    Wire *child = static_cast<Wire *>(itemAt(event->pos()));
                    deleteWire(child);
                }

                switch(child->getGateType())
                {
                case Buffer:
                case Not:
                case And:
                case Or:
                case Nand:
                case Nor:
                case Xor:
                case Xnor:
                    deleteGate(child);
                    break;

                case ClockGate:
                {
                    Clock *child = static_cast<Clock *>(itemAt(event->pos()));
                    deleteClock(child);
                }
                    break;

                case UserInput:
                case UserOutput:
                {
                    UserIO *child = static_cast<UserIO *>(itemAt(event->pos()));
                    deleteUserIO(child);
                }
                    break;

                case NumericInput:
                case NumericOutput:
                {
                    NumericIO *child = static_cast<NumericIO *>(itemAt(event->pos()));
                    deleteNumericIO(child);
                }
                    break;

                case MultiPlexer:
                {
                    Multiplexer *child = static_cast<Multiplexer *>(itemAt(event->pos()));
                    deleteMultiplexer(child);
                }
                    break;

                case FlipFlop:
                {
                    Flipflop *child = static_cast<Flipflop *>(itemAt(event->pos()));
                    deleteFlipflop(child);
                }
                    break;

                case CounterGate:
                {
                    Counter *child = static_cast<Counter *>(itemAt(event->pos()));
                    deleteCounter(child);
                }
                    break;

                default:
                    break;
                }
            }
            return;
        }

        Gate *child = static_cast<Gate *>(itemAt(event->pos()));
        if (!child)
        {
            wireDrawing=false;
            if(startPin != 0)
            {
                startPin->select(false);
                startPin=0;
            }
            return;
        }
        movinggate = child;
        oldPos = movinggate->pos();

        QGraphicsView::mousePressEvent(event);
    }
}

void graphWidget::mouseReleaseEvent(QMouseEvent *event)
{
    if(iscomponentswidget==false)
    {
        if (movinggate != 0 && event->button() == Qt::LeftButton)
        {
            if (oldPos != movinggate->pos())
                Widget::simulator()->itemMoved(movinggate,oldPos);
            movinggate = 0;
        }

        QGraphicsView::mouseReleaseEvent(event);
    }
    setCursor(Qt::OpenHandCursor);
}

void graphWidget::dragEnterEvent(QDragEnterEvent *event)
{
    if (event->mimeData()->hasFormat("Gate"))
    {
        event->setAccepted(true);
        dragOver = true;
        update();
    }
    else
    {
        event->setAccepted(false);
    }
}

void graphWidget::dragLeaveEvent(QDragLeaveEvent *)
{
    dragOver = false;
    update();
}

void graphWidget::dragMoveEvent(QDragMoveEvent *event)
{
    if (event->mimeData()->hasFormat("Gate"))
    {
        if (event->source() == this)
        {
            event->setDropAction(Qt::MoveAction);
            event->accept();
        }
        else
        {
            event->acceptProposedAction();
        }
    }
    else
    {
        event->ignore();
    }
}

void graphWidget::dropEvent(QDropEvent *event)
{
    dragOver = false;
    if(iscomponentswidget==false)
    {
        if (event->mimeData()->hasFormat("Gate"))
        {
            QByteArray itemData = event->mimeData()->data("Gate");
            QDataStream dataStream(&itemData, QIODevice::ReadOnly);

            //enum not supported!
            int type;
            QPoint offset;
            dataStream >> type >> offset;

            //offset not used!
            addItem(type,mapToScene(event->pos()));

            if (event->source() == this)
            {
                event->setDropAction(Qt::MoveAction);
                event->accept();
            }
            else
            {
                event->acceptProposedAction();
            }
        }
        else
        {
            event->ignore();
        }
    }
    else
    {
        QGraphicsView::dropEvent(event);
    }
    update();

    setCursor(Qt::OpenHandCursor);
}

void graphWidget::timerEvent(QTimerEvent *)
{
    if(iscomponentswidget==false)
    {
        foreach (Gate *gate, gates)
        {
            gate->outputStateAdjust();
        }
        foreach (Clock *gate, clocks)
        {
            gate->outputStateAdjust();
        }
        foreach (UserIO *gate, userios)
        {
            gate->outputStateAdjust();
        }
        foreach (NumericIO *gate, numericios)
        {
            gate->outputStateAdjust();
        }
        foreach (Multiplexer *gate, multiplexers)
        {
            gate->outputStateAdjust();
        }
        foreach (Flipflop *gate, flipflops)
        {
            gate->outputStateAdjust();
        }
        foreach (Counter *gate, counters)
        {
            gate->outputStateAdjust();
        }

        foreach (Gate *gate, gates)
        {
            gate->inputStateAdjust();
        }
        foreach (Clock *gate, clocks)
        {
            gate->inputStateAdjust();
        }
        foreach (UserIO *gate, userios)
        {
            gate->inputStateAdjust();
        }
        foreach (NumericIO *gate, numericios)
        {
            gate->inputStateAdjust();
        }
        foreach (Multiplexer *gate, multiplexers)
        {
            gate->inputStateAdjust();
        }
        foreach (Flipflop *gate, flipflops)
        {
            gate->inputStateAdjust();
        }
        foreach (Counter *gate, counters)
        {
            gate->inputStateAdjust();
        }
    }
}
