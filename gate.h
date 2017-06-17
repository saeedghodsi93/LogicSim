#ifndef GATE_H
#define GATE_H
#include <QApplication>

#include <QGraphicsProxyWidget>
#include <QGraphicsPixMapItem>
#include <QPainter>
#include <QStyleOption>

#include <QDrag>
#include <QDragEnterEvent>
#include <QDropEvent>
#include <QMimeData>

class Widget;
class Wire;
class Pin;
QT_BEGIN_NAMESPACE
class QGraphicsSceneMouseEvent;
QT_END_NAMESPACE

enum gateType{Buffer,Not,And,Or,Nand,Nor,Xor,Xnor,ClockGate,UserInput,UserOutput,NumericInput,NumericOutput,MultiPlexer,FlipFlop,CounterGate};

class Gate : public QGraphicsPixmapItem
{
public:
    Gate(enum gateType type= Buffer);
    Gate(int type);//for passing gatetype in drop

    virtual void inputStateAdjust();
    virtual void outputStateAdjust();

    virtual QList<Pin *> InputList();
    virtual QList<Pin *> OutputList();
    int getGateIndex();
    void setGateIndex(int idx);
    enum itemType getItemType();
    enum gateType getGateType();
    QPointF getPos();

protected:
    QVariant itemChange(GraphicsItemChange change, const QVariant &value);
    QPainterPath shape() const;

private:
    enum itemType itemtype;
    enum gateType gatetype;
    int index;

    void BUFFER(bool isIcon= true);
    void NOT(bool isIcon= true);
    void AND(bool isIcon= true);
    void OR(bool isIcon= true);
    void NAND(bool isIcon= true);
    void NOR(bool isIcon= true);
    void XOR(bool isIcon= true);
    void XNOR(bool isIcon= true);

    void BUFFERStateAdjust();
    void NOTStateAdjust();
    void ANDStateAdjust();
    void ORStateAdjust();
    void NANDStateAdjust();
    void NORStateAdjust();
    void XORStateAdjust();
    void XNORStateAdjust();

    QList<Pin *> inputList;
    QList<Pin *> outputList;
};

#endif // GATE_H
