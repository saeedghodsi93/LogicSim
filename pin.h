#ifndef PIN_H
#define PIN_H
#include <QApplication>
#include <QList>

#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsColorizeEffect>
#include <QPainter>
#include <QStyleOption>

#include <QDrag>
#include <QDragEnterEvent>
#include <QDropEvent>
#include <QMimeData>

class Widget;
class graphWidget;
class Gate;
class Wire;
QT_BEGIN_NAMESPACE
class QGraphicsSceneMouseEvent;
QT_END_NAMESPACE

enum pinType{InputPin,OutputPin};

class Pin : public QGraphicsItem
{
public:
    Pin(Gate *pargate= 0, QPoint relPosition= QPoint(5,25), pinType type= InputPin, bool isicon= true, int idx= 0);

    int getPinIndex();
    enum itemType getItemType();
    enum pinType getPinType();
    bool getPinState();
    void setPinState(bool state);
    void toggleState();
    Gate *parentGate() const;
    QList<Wire *> connectedWires() const;

    void addWire(Wire *wire);
    void deleteWire(Wire *wire);
    void positionAdjust();
    void select(bool selected= false);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void paintEvent(QPaintEvent *);
    QRectF boundingRect() const;
    QPainterPath shape() const;

private:
    void setHigh();
    void setLow();

    QGraphicsColorizeEffect *effect;
    enum itemType itemtype;
    enum pinType pintype;
    bool pinstate;
    bool isIcon;
    qreal size;
    QColor color;
    QColor darkcolor;
    Gate *gate;
    QList<Wire *> wires;
    QPoint position;
    int index;
};

#endif // PIN_H
