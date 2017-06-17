#ifndef WIDGET_H
#define WIDGET_H
#include <QWidget>
#include <QMenuBar>
#include <QMenu>
#include <QToolBar>
#include <QStatusBar>
#include <QSettings>
#include <QMessageBox>
#include <QFileDialog>
#include <QUndoStack>

class graphWidget;
class Gate;
class Clock;
class UserIO;
class NumericIO;
class Multiplexer;
class Flipflop;
class Counter;
class Pin;
class Wire;
class MoveCommand;
class AddCommand;

namespace Ui
{
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    ~Widget();
    static Widget *simulator();
    graphWidget *BoardGraph();
    graphWidget *ComponentsGraph();
    void showDelay(int delay);

    void itemMoved(Gate *movedGate, const QPointF &Position);
    void itemAdded(Gate *addedGate);
    void itemAdded(Clock *addedGate);
    void itemAdded(UserIO *addedGate);
    void itemAdded(NumericIO *addedGate);
    void itemAdded(Multiplexer *addedGate);
    void itemAdded(Flipflop *addedGate);
    void itemAdded(Counter *addedGate);

    MoveCommand *lastMoveCommand();

protected:
    void closeEvent(QCloseEvent *event);

private slots:
    void on_component_Type_currentIndexChanged(int index);
    void on_Speed_sliderMoved(int position);

    void newFile();
    bool save();
    bool saveAs();
    void load();
    void about();

private:
    explicit Widget(QWidget *parent = 0);
    Ui::Widget *ui;

    void initialize();

    void createActions();
    void createMenus();
    void createToolBar();
    void readSettings();
    void writeSettings();
    bool maybeSave();
    bool saveFile(const QString &fileName);
    void loadFile(const QString &fileName);
    void setCurrentFile(const QString &fileName);
    QString strippedName(const QString &fullFileName);

    QString curFile;
    QMenuBar *simulatorMenuBar;
    QMenu *fileMenu;
    QMenu *editMenu;
    QMenu *helpMenu;
    QToolBar *fileToolBar;
    QAction *newAct;
    QAction *saveAct;
    QAction *saveAsAct;
    QAction *loadAct;
    QAction *undoAct;
    QAction *redoAct;
    QAction *exitAct;
    QAction *aboutAct;
    QAction *aboutQtAct;
    QUndoStack *undoStack;
    MoveCommand *lastmovecommand;

    static Widget *instance;
    graphWidget *boardGraph;
    graphWidget *componentsGraph;
};

#endif  // WIDGET_H
