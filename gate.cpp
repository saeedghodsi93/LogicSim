#include "widget.h"
#include "graphwidget.h"
#include "wire.h"
#include "pin.h"
#include "gate.h"

Gate::Gate(gateType type)
    : itemtype(gate),gatetype(type)
{
    setFlag(ItemIsMovable);
    setFlag(ItemSendsGeometryChanges);
    setCacheMode(DeviceCoordinateCache);
    setZValue(-1);

    switch(type)
    {
    case Buffer:
        BUFFER(true);
        break;

    case Not:
        NOT(true);
        break;

    case And:
        AND(true);
        break;

    case Or:
        OR(true);
        break;

    case Nand:
        NAND(true);
        break;

    case Nor:
        NOR(true);
        break;

    case Xor:
        XOR(true);
        break;

    case Xnor:
        XNOR(true);
        break;

    default:
        break;
    }
}

Gate::Gate(int type)
    : itemtype(gate)
{
    setFlag(ItemIsMovable);
    setFlag(ItemSendsGeometryChanges);
    setCacheMode(DeviceCoordinateCache);
    setZValue(-1);

    switch(type)
    {
    case 0:
        gatetype=Buffer;
        BUFFER(false);
        break;

    case 1:
        gatetype=Not;
        NOT(false);
        break;

    case 2:
        gatetype=And;
        AND(false);
        break;

    case 3:
        gatetype=Or;
        OR(false);
        break;

    case 4:
        gatetype=Nand;
        NAND(false);
        break;

    case 5:
        gatetype=Nor;
        NOR(false);
        break;

    case 6:
        gatetype=Xor;
        XOR(false);
        break;

    case 7:
        gatetype=Xnor;
        XNOR(false);
        break;

    case 8:
        gatetype=ClockGate;
        break;

    case 9:
        gatetype=UserInput;
        break;

    case 10:
        gatetype=UserOutput;
        break;

    case 11:
        gatetype=NumericInput;
        break;

    case 12:
        gatetype=NumericOutput;
        break;

    case 13:
        gatetype=MultiPlexer;
        break;

    case 14:
        gatetype=FlipFlop;
        break;

    case 15:
        gatetype=CounterGate;
        break;

    default:
        break;
    }
}

void Gate::inputStateAdjust()
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

void Gate::outputStateAdjust()
{
    switch(gatetype)
    {
    case Buffer:
        BUFFERStateAdjust();
        break;

    case Not:
        NOTStateAdjust();
        break;

    case And:
        ANDStateAdjust();
        break;

    case Or:
        ORStateAdjust();
        break;

    case Nand:
        NANDStateAdjust();
        break;

    case Nor:
        NORStateAdjust();
        break;

    case Xor:
        XORStateAdjust();
        break;

    case Xnor:
        XNORStateAdjust();
        break;

    default:
        break;
    }
}

QList<Pin *> Gate::InputList()
{
    return inputList;
}

QList<Pin *> Gate::OutputList()
{
    return outputList;
}

itemType Gate::getItemType()
{
    return itemtype;
}

gateType Gate::getGateType()
{
    return gatetype;
}

QPointF Gate::getPos()
{
    return pos();
}

void Gate::BUFFER(bool isIcon)
{
    QPixmap pixmap;
    if(isIcon==true)
    {
        pixmap.load("C:/Images/BUFFERICON.PNG");
        inputList << (new Pin(this,QPoint(5,25),InputPin,true));
        outputList << (new Pin(this,QPoint(95,25),OutputPin,true));
    }
    else
    {
        pixmap.load("C:/Images/BUFFER.PNG");
        inputList << (new Pin(this,QPoint(5,95),InputPin,false,0));
        outputList << (new Pin(this,QPoint(300,95),OutputPin,false,0));
    }
    setPixmap(pixmap);
}

void Gate::NOT(bool isIcon)
{
    QPixmap pixmap;
    if(isIcon==true)
    {
        pixmap.load("C:/Images/NOTICON.PNG");
        inputList << (new Pin(this,QPoint(5,25),InputPin,true));
        outputList << (new Pin(this,QPoint(95,25),OutputPin,true));
    }
    else
    {
        pixmap.load("C:/Images/NOT.PNG");
        inputList << (new Pin(this,QPoint(5,95),InputPin,false,0));
        outputList << (new Pin(this,QPoint(320,95),OutputPin,false,0));
    }
    setPixmap(pixmap);
}

void Gate::AND(bool isIcon)
{
    QPixmap pixmap;
    if(isIcon==true)
    {
        pixmap.load("C:/Images/ANDICON.PNG");
        inputList << (new Pin(this,QPoint(5,15),InputPin,true));
        inputList << (new Pin(this,QPoint(5,35),InputPin,true));
        outputList << (new Pin(this,QPoint(95,25),OutputPin,true));
    }
    else
    {
        pixmap.load("C:/Images/AND.PNG");
        inputList << (new Pin(this,QPoint(5,42),InputPin,false,0));
        inputList << (new Pin(this,QPoint(5,120),InputPin,false,1));
        outputList << (new Pin(this,QPoint(310,80),OutputPin,false,0));
    }
    setPixmap(pixmap);
}

void Gate::OR(bool isIcon)
{
    QPixmap pixmap;
    if(isIcon==true)
    {
        pixmap.load("C:/Images/ORICON.PNG");
        inputList << (new Pin(this,QPoint(5,15),InputPin,true));
        inputList << (new Pin(this,QPoint(5,35),InputPin,true));
        outputList << (new Pin(this,QPoint(95,25),OutputPin,true));
    }
    else
    {
        pixmap.load("C:/Images/OR.PNG");
        inputList << (new Pin(this,QPoint(5,48),InputPin,false,0));
        inputList << (new Pin(this,QPoint(5,125),InputPin,false,1));
        outputList << (new Pin(this,QPoint(310,87),OutputPin,false,0));
    }
    setPixmap(pixmap);
}

void Gate::NAND(bool isIcon)
{
    QPixmap pixmap;
    if(isIcon==true)
    {
        pixmap.load("C:/Images/NANDICON.PNG");
        inputList << (new Pin(this,QPoint(5,15),InputPin,true));
        inputList << (new Pin(this,QPoint(5,35),InputPin,true));
        outputList << (new Pin(this,QPoint(95,25),OutputPin,true));
    }
    else
    {
        pixmap.load("C:/Images/NAND.PNG");
        inputList << (new Pin(this,QPoint(5,42),InputPin,false,0));
        inputList << (new Pin(this,QPoint(5,120),InputPin,false,1));
        outputList << (new Pin(this,QPoint(330,80),OutputPin,false,0));
    }
    setPixmap(pixmap);
}

void Gate::NOR(bool isIcon)
{
    QPixmap pixmap;
    if(isIcon==true)
    {
        pixmap.load("C:/Images/NORICON.PNG");
        inputList << (new Pin(this,QPoint(5,15),InputPin,true));
        inputList << (new Pin(this,QPoint(5,35),InputPin,true));
        outputList << (new Pin(this,QPoint(95,25),OutputPin,true));
    }
    else
    {
        pixmap.load("C:/Images/NOR.PNG");
        inputList << (new Pin(this,QPoint(5,48),InputPin,false,0));
        inputList << (new Pin(this,QPoint(5,125),InputPin,false,1));
        outputList << (new Pin(this,QPoint(330,87),OutputPin,false,0));
    }
    setPixmap(pixmap);
}

void Gate::XOR(bool isIcon)
{
    QPixmap pixmap;
    if(isIcon==true)
    {
        pixmap.load("C:/Images/XORICON.PNG");
        inputList << (new Pin(this,QPoint(5,15),InputPin,true));
        inputList << (new Pin(this,QPoint(5,35),InputPin,true));
        outputList << (new Pin(this,QPoint(95,25),OutputPin,true));
    }
    else
    {
        pixmap.load("C:/Images/XOR.PNG");
        inputList << (new Pin(this,QPoint(5,44),InputPin,false,0));
        inputList << (new Pin(this,QPoint(5,122),InputPin,false,1));
        outputList << (new Pin(this,QPoint(330,82),OutputPin,false,0));
    }
    setPixmap(pixmap);
}

void Gate::XNOR(bool isIcon)
{
    QPixmap pixmap;
    if(isIcon==true)
    {
        pixmap.load("C:/Images/XNORICON.PNG");
        inputList << (new Pin(this,QPoint(5,15),InputPin,true));
        inputList << (new Pin(this,QPoint(5,35),InputPin,true));
        outputList << (new Pin(this,QPoint(95,25),OutputPin,true));
    }
    else
    {
        pixmap.load("C:/Images/XNOR.PNG");
        inputList << (new Pin(this,QPoint(5,44),InputPin,false,0));
        inputList << (new Pin(this,QPoint(5,122),InputPin,false,1));
        outputList << (new Pin(this,QPoint(360,82),OutputPin,false,0));
    }
    setPixmap(pixmap);
}

int Gate::getGateIndex()
{
    return index;
}

void Gate::setGateIndex(int idx)
{
    index=idx;
}

void Gate::BUFFERStateAdjust()
{
    outputList[0]->setPinState(inputList[0]->getPinState());
}

void Gate::NOTStateAdjust()
{
    outputList[0]->setPinState(!(inputList[0]->getPinState()));
}

void Gate::ANDStateAdjust()
{
    outputList[0]->setPinState((inputList[0]->getPinState()) & (inputList[1]->getPinState()));
}

void Gate::ORStateAdjust()
{
    outputList[0]->setPinState((inputList[0]->getPinState()) | (inputList[1]->getPinState()));
}

void Gate::NANDStateAdjust()
{
    outputList[0]->setPinState(!((inputList[0]->getPinState()) & (inputList[1]->getPinState())));
}

void Gate::NORStateAdjust()
{
    outputList[0]->setPinState(!((inputList[0]->getPinState()) | (inputList[1]->getPinState())));
}

void Gate::XORStateAdjust()
{
    outputList[0]->setPinState((inputList[0]->getPinState()) ^ (inputList[1]->getPinState()));
}

void Gate::XNORStateAdjust()
{
    outputList[0]->setPinState(!((inputList[0]->getPinState()) ^ (inputList[1]->getPinState())));
}

QVariant Gate::itemChange(GraphicsItemChange change, const QVariant &value)
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

QPainterPath Gate::shape() const
{
    QPainterPath path;
    path.addRect(20, 0, 250, 200);
    return path;
}
