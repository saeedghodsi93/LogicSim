#ifndef GRAPHWIDGET_H
#define GRAPHWIDGET_H
#include <QGraphicsView>
#include <QTime>

#include <QtMath>
#include <QKeyEvent>
#include <QPainter>

#include <QDrag>
#include <QDragEnterEvent>
#include <QDropEvent>
#include <QMimeData>
#include <QImage>

class Widget;
class Gate;
class Clock;
class UserIO;
class NumericIO;
class Multiplexer;
class Flipflop;
class Counter;
class Wire;
class Pin;

enum graphType{board,components};
enum itemType{gate,pin,wire,clockdisplay,numericdisplay,counterdisplay,label,base,resetlabel};

class graphWidget : public QGraphicsView
{
    Q_OBJECT

public:
    graphWidget(enum graphType type, QWidget *parent= 0);
    ~graphWidget();

    void basicGates();
    void compoundGates();
    void ioGates();
    void additionalGates();
    void resetTimer(int position);

    void startDrawing(Pin *pin);
    void finishDrawing(Pin *endPin= 0);
    bool isDrawing();
    void addItem(int type,QPointF pos);
    Gate *addGate(int type, QPointF pos, bool isForUndo= false);
    Clock *addClock(QPointF pos, bool isForUndo= false, int period= 1000);
    UserIO *addUserIO(int type, QPointF pos, bool isForUndo= false, bool state= false);
    NumericIO *addNumericIO(int type, QPointF pos, bool instantDraw= false, bool isForUndo= false, int bits= 2, int value= 0, int numbase= 10);
    Multiplexer *addMultiplexer(QPointF pos, bool instantDraw= false, bool isForUndo= false, int bits= 2);
    Flipflop *addFlipflop(QPointF pos, bool isForUndo= false);
    Counter *addCounter(QPointF pos, bool instantDraw= false, bool isForUndo= false, int bits= 2, int value= 0);
    void deleteGate(Gate *gate);
    void deleteClock(Clock *gate);
    void deleteUserIO(UserIO *gate);
    void deleteNumericIO(NumericIO *gate);
    void deleteMultiplexer(Multiplexer *gate);
    void deleteFlipflop(Flipflop *gate);
    void deleteCounter(Counter *gate);
    void addWire(Pin *startPin, Pin *endPin);
    void addWire(int sourceGateType, int sourceGateIndex, int sourcePinIndex,
                 int destGateType, int destGateIndex, int destPinIndex);
    void deleteWire(Wire *wire);

    QGraphicsScene *scene();
    QList<Gate *> getGates();
    QList<Clock *> getClocks();
    QList<UserIO *> getUserIOs();
    QList<NumericIO *> getNumericIOs();
    QList<Multiplexer *> getMultiplexers();
    QList<Flipflop *> getFlipflops();
    QList<Counter *>getCounters();
    QList<Wire *> getWires();

public slots:
    void zoomIn();
    void zoomOut();

protected:
    void timerEvent(QTimerEvent *);

    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void dragEnterEvent(QDragEnterEvent *event);
    void dragLeaveEvent(QDragLeaveEvent *);
    void dragMoveEvent(QDragMoveEvent *event);
    void dropEvent(QDropEvent *event);

    void keyPressEvent(QKeyEvent *event);
#ifndef QT_NO_WHEELEVENT
    void wheelEvent(QWheelEvent *event);
#endif

private:
    void Board();
    void Components();
    void scaleView(qreal scaleFactor);

    Gate *BUFFER;
    Gate *NOT;
    Gate *AND;
    Gate *OR;
    Gate *NAND;
    Gate *NOR;
    Gate *XOR;
    Gate *XNOR;
    Clock *CLOCK;
    UserIO *USERINPUT;
    UserIO *USEROUTPUT;
    NumericIO *NUMERICINPUT;
    NumericIO *NUMERICOUTPUT;
    Multiplexer *MULTIPLEXER;
    Flipflop *FLIPFLOP;
    Counter *COUNTER;

    QGraphicsScene *graphScene;
    QList<Gate *> gates;
    QList<Clock *> clocks;
    QList<UserIO *> userios;
    QList<NumericIO *> numericios;
    QList<Multiplexer *> multiplexers;
    QList<Flipflop *> flipflops;
    QList<Counter *> counters;
    QList<Wire *> wires;
    Pin *startPin;
    Gate *movinggate;
    QPointF oldPos;
    bool wireDrawing;
    bool dragOver;
    int timerID;
    int delay;
    bool iscomponentswidget;
};

#endif // GRAPHWIDGET_H
