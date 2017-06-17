#include "widget.h"
#include "graphwidget.h"
#include "gate.h"
#include "wire.h"
#include "pin.h"

Wire::Wire(Pin *sourcePin, Pin *destPin)
    : source(sourcePin),dest(destPin)
{
    setAcceptedMouseButtons(0);
    source->addWire(this);
    dest->addWire(this);
    positionAdjust();
    itemtype=wire;
    wireState=source->getPinState();
    dest->setPinState(source->getPinState());
    color=QColor(Qt::darkCyan);
}

itemType Wire::getItemType()
{
    return itemtype;
}

Pin *Wire::sourcePin() const
{
    return source;
}

Pin *Wire::destPin() const
{
    return dest;
}

void Wire::positionAdjust()
{
    if (!source || !dest)
        return;

    QLineF line(mapFromItem(source, 0, 0), mapFromItem(dest, 0, 0));
    qreal length = line.length();

    prepareGeometryChange();

    if (length > qreal(40.))
    {
        QPointF edgeOffset((line.dx() * 20) / length, (line.dy() * 20) / length);
        sourcePoint = line.p1() + edgeOffset;
        destPoint = line.p2() - edgeOffset;
    }
    else
    {
        sourcePoint = destPoint = line.p1();
    }
}

void Wire::setHigh()
{
    color=QColor(Qt::darkRed);
    update();
}

void Wire::setLow()
{
    color=QColor(Qt::darkCyan);
    update();
}

void Wire::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    if (!source || !dest)
        return;

    QLineF line(sourcePoint, destPoint);
    if (qFuzzyCompare(line.length(), qreal(0.)))
        return;

    painter->setPen(QPen(color, 10, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    painter->drawLine(line);
}

void Wire::paintEvent(QPaintEvent *)
{
    if (!source || !dest)
        return;

    QLineF line(sourcePoint, destPoint);
    if (qFuzzyCompare(line.length(), qreal(0.)))
        return;

    QPainter *painter;
    painter->setPen(QPen(color, 10, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    painter->drawLine(line);
}

QRectF Wire::boundingRect() const
{
    if (!source || !dest)
        return QRectF();

    qreal penWidth = 10;
    qreal extra = (penWidth) / 2.0;

    return QRectF(sourcePoint, QSizeF(destPoint.x() - sourcePoint.x(),
                                      destPoint.y() - sourcePoint.y()))
        .normalized()
            .adjusted(-extra, -extra, extra, extra);
}
