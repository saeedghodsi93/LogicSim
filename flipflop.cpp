#include "widget.h"
#include "graphwidget.h"
#include "pin.h"
#include "wire.h"
#include "mainwindow.h"
#include "flipflop.h"

Flipflop::Flipflop(bool isIcon)
    : Gate(FlipFlop)
{
    QPixmap pixmap;
    state=false;
    if(isIcon==true)
    {
        pixmap.load("C:/Images/FLIPFLOPICON.PNG");
        inputList << (new Pin(this,QPoint(5,28),OutputPin,true));
        inputList << (new Pin(this,QPoint(49,-3),OutputPin,true));
        outputList << (new Pin(this,QPoint(95,28),OutputPin,true));
    }
    else
    {
        pixmap.load("C:/Images/FLIPFLOP.PNG");
        inputList << (new Pin(this,QPoint(27,95),InputPin,false,0));
        inputList << (new Pin(this,QPoint(158,5),InputPin,false,1));
        outputList << (new Pin(this,QPoint(295,95),OutputPin,false,0));
    }
    setPixmap(pixmap);
}

void Flipflop::inputStateAdjust()
{
    foreach (Pin *pin, inputList)
    {
        if(pin->connectedWires().isEmpty()==false)
        {
            pin->setPinState(pin->connectedWires()[0]->sourcePin()->getPinState());
        }
        else
        {
            pin->setPinState(false);
        }
    }
}

void Flipflop::outputStateAdjust()
{
    if(state==true && inputList[0]->getPinState()==false)
        outputList[0]->setPinState(inputList[1]->getPinState());
    state=inputList[0]->getPinState();
}

QList<Pin *> Flipflop::InputList()
{
    return inputList;
}

QList<Pin *> Flipflop::OutputList()
{
    return outputList;
}

QVariant Flipflop::itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant &value)
{
    switch (change)
    {
    case ItemPositionHasChanged:
        foreach (Pin *pin, inputList)
            pin->positionAdjust();
        foreach (Pin *pin, outputList)
            pin->positionAdjust();
        break;

    default:
        break;
    };
    return QGraphicsItem::itemChange(change, value);
}

QPainterPath Flipflop::shape() const
{
    QPainterPath path;
    path.addRect(20, 0, 250, 200);
    return path;
}
