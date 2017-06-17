#include "widget.h"
#include "graphwidget.h"
#include "gate.h"
#include "wire.h"
#include "pin.h"

Pin::Pin(Gate *pargate, QPoint relPosition, pinType type, bool isicon, int idx)
    : gate(pargate),position(relPosition),isIcon(isicon),pintype(type),index(idx)
{
    setFlag(ItemSendsGeometryChanges);
    //setFlag(ItemIsSelectable);
    setCacheMode(DeviceCoordinateCache);
    setZValue(-1);
    setParentItem(gate);
    setPos(relPosition);
    itemtype=pin;
    pinstate=false;
    if(isIcon==true)
        size=8;
    else
        size=20;
    color=QColor(Qt::cyan);
    darkcolor=QColor(Qt::darkCyan);
}

int Pin::getPinIndex()
{
    return index;
}

itemType Pin::getItemType()
{
    return itemtype;
}

pinType Pin::getPinType()
{
    return pintype;
}

bool Pin::getPinState()
{
    return pinstate;
}

void Pin::setPinState(bool state)
{
    pinstate=state;
    if(pinstate==true)
        setHigh();
    else
        setLow();
}

void Pin::toggleState()
{
    if(pinstate==true)
    {
        pinstate=false;
        setLow();
    }
    else
    {
        pinstate=true;
        setHigh();
    }
}

void Pin::addWire(Wire *wire)
{
    wires << wire;
    wire->positionAdjust();
}

void Pin::deleteWire(Wire *wire)
{
    wires.removeOne(wire);
}

void Pin::positionAdjust()
{
    foreach (Wire *wire, wires)
        wire->positionAdjust();
}

void Pin::select(bool selected)
{
    if(selected==true)
    {
        effect = new QGraphicsColorizeEffect();
        effect->setColor(Qt::yellow);
        setGraphicsEffect(effect);
    }
    else
    {
        setGraphicsEffect(0);
    }
}

void Pin::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(!(event->buttons() & Qt::LeftButton))
        return ;

    if(isIcon==true)
        return;

    if(Widget::simulator()->BoardGraph()->isDrawing() == false)
        Widget::simulator()->BoardGraph()->startDrawing(this);
    else
        Widget::simulator()->BoardGraph()->finishDrawing(this);
}

Gate *Pin::parentGate() const
{
    return gate;
}

QList<Wire *> Pin::connectedWires() const
{
    return wires;
}

void Pin::setHigh()
{
    foreach (Wire *wire, connectedWires())
    {
        wire->setHigh();
    }
    color=QColor(Qt::red);
    darkcolor=QColor(Qt::darkRed);
    update();
}

void Pin::setLow()
{
    foreach (Wire *wire, connectedWires())
    {
        wire->setLow();
    }
    color=QColor(Qt::cyan);
    darkcolor=QColor(Qt::darkCyan);
    update();
}

void Pin::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *)
{
    painter->setPen(Qt::NoPen);
    painter->setBrush(Qt::black);
    painter->drawEllipse( -size+2, -size+2, 2*size, 2*size);

    QRadialGradient gradient(-3, -3, size);
    if (option->state & QStyle::State_Sunken)
    {
        gradient.setCenter(3, 3);
        gradient.setFocalPoint(3, 3);
        gradient.setColorAt(1, QColor(color).light(120));
        gradient.setColorAt(0, QColor(darkcolor).light(120));
    }
    else
    {
        gradient.setColorAt(0, color);
        gradient.setColorAt(1, darkcolor);
    }
    painter->setBrush(gradient);

    painter->setPen(QPen(Qt::black, 0));
    painter->drawEllipse(-size, -size, 2*size, 2*size);
}

void Pin::paintEvent(QPaintEvent *)
{
    QPainter *painter;
    const QStyleOptionGraphicsItem *option;

    painter->setPen(Qt::NoPen);
    painter->setBrush(Qt::black);
    painter->drawEllipse( -size+2, -size+2, 2*size, 2*size);

    QRadialGradient gradient(-3, -3, size);
    if (option->state & QStyle::State_Sunken)
    {
        gradient.setCenter(3, 3);
        gradient.setFocalPoint(3, 3);
        gradient.setColorAt(1, QColor(color).light(120));
        gradient.setColorAt(0, QColor(darkcolor).light(120));
    }
    else
    {
        gradient.setColorAt(0, color);
        gradient.setColorAt(1, darkcolor);
    }
    painter->setBrush(gradient);

    painter->setPen(QPen(Qt::black, 0));
    painter->drawEllipse(-size, -size, 2*size, 2*size);
}

QPainterPath Pin::shape() const
{
    QPainterPath path;
    path.addEllipse(-10, -10, 50, 50);
    return path;
}

QRectF Pin::boundingRect() const
{
    qreal adjust = 2;
    return QRectF( -size - adjust, -size - adjust, 2*size + 3 + adjust, 2*size + 3 + adjust);
}
