#ifndef WIRE_H
#define WIRE_H
#include <QGraphicsItem>

#include <QtMath>
#include <QPainter>
#include <QPaintEvent>

class Widget;
class graphWidget;
class Gate;
class Pin;

class Wire : public QGraphicsItem
{
public:
    Wire(Pin *sourcePin=0, Pin *destPin=0);

    enum itemType getItemType();

    Pin *sourcePin() const;
    Pin *destPin() const;
    void positionAdjust();
    void setHigh();
    void setLow();

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void paintEvent(QPaintEvent *);
    QRectF boundingRect() const;

private:
    enum itemType itemtype;
    bool wireState;
    Pin *source, *dest;
    QPointF sourcePoint;
    QPointF destPoint;
    QColor color;
};

#endif // WIRE_H
