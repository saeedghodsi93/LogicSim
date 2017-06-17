#include "graphwidget.h"
#include "gate.h"
#include "pin.h"
#include "wire.h"
#include "userio.h"

UserIO::UserIO(gateType type)
    : Gate(type)
{
    QPixmap pixmap;
    switch(type)
    {
    case UserInput:
        pixmap.load("C:/Images/USERINPUTICON.PNG");
        outputList << (new Pin(this,QPoint(95,25),OutputPin,true));
        break;

    case UserOutput:
        pixmap.load("C:/Images/USEROUTPUTICON.PNG");
        inputList << (new Pin(this,QPoint(5,25),InputPin,true));
        break;

    default:
        break;
    }
    setPixmap(pixmap);
}

UserIO::UserIO(int type, bool st)
    : Gate(type),state(st)
{
    QPixmap pixmap;
    QGraphicsProxyWidget *proxy = new QGraphicsProxyWidget(this);
    switch(type)
    {
    case 9:
        pixmap.load("C:/Images/USERINPUT.PNG");
        label = new Label(this,state,QPoint(43,31),InputLabel);
        outputList << (new Pin(this,QPoint(300,82),OutputPin,false,0));
        break;

    case 10:
        pixmap.load("C:/Images/USEROUTPUT.PNG");
        label = new Label(this,state,QPoint(81,31),OutputLabel);
        inputList << (new Pin(this,QPoint(5,80),InputPin,false,0));
        break;

    default:
        break;
    }
    proxy->setWidget(label);
    setPixmap(pixmap);
}

void UserIO::inputStateAdjust()
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

void UserIO::outputStateAdjust()
{
    switch(getGateType())
    {
    case UserInput:
        outputList[0]->setPinState(label->getLabelState());
        break;

    case UserOutput:
        label->setLabelState();
        break;

    default:
        break;
    }
}

QList<Pin *> UserIO::InputList()
{
    return inputList;
}

QList<Pin *> UserIO::OutputList()
{
    return outputList;
}

bool UserIO::getState()
{
    return state;
}

void UserIO::setState(bool st)
{
    state=st;
}

QVariant UserIO::itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant &value)
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

QPainterPath UserIO::shape() const
{
    QPainterPath path;
    path.addRect(20, 0, 250, 200);
    return path;
}

/******************************************************************************************/
/******************************************************************************************/

Label::Label(UserIO *pargate, bool labelState, QPoint relPosition, labelType type)
    : gate(pargate),state(labelState),position(relPosition),itemtype(label),labeltype(type)
{
    move(position);
    resize(QSize(50,100));
    if(state==true)
    {
        setStyleSheet("border-width: 2px;"
                      "border-radius: 3px;"
                      "border-style: outset;"
                      "border-color: darkBlue;"
                      "background-color: darkRed");
    }
    else
    {
        setStyleSheet("border-width: 2px;"
                      "border-radius: 3px;"
                      "border-style: outset;"
                      "border-color: darkBlue;"
                      "background-color: darkCyan");
    }
}

void Label::setLabelState()
{
    if(gate->InputList()[0]->getPinState()==true)
    {
        state=true;
        gate->setState(state);
        setStyleSheet("border-width: 2px;"
                      "border-radius: 3px;"
                      "border-style: outset;"
                      "border-color: darkBlue;"
                      "background-color: darkRed");
    }
    else
    {
        state=false;
        gate->setState(state);
        setStyleSheet("border-width: 2px;"
                      "border-radius: 3px;"
                      "border-style: outset;"
                      "border-color: darkBlue;"
                      "background-color: darkCyan");
    }
}

bool Label::getLabelState()
{
    return state;
}

itemType Label::getItemType()
{
    return itemtype;
}

UserIO *Label::parentGate() const
{
    return gate;
}

void Label::mousePressEvent(QMouseEvent *event)
{
    if(labeltype==InputLabel)
    {
        if (!(event->buttons() & Qt::LeftButton))
                return;

        toggleState();
    }
}

void Label::toggleState()
{
    if(state==true)
    {
        state=false;
        gate->setState(state);
        setStyleSheet("border-width: 2px;"
                      "border-radius: 3px;"
                      "border-style: outset;"
                      "border-color: darkBlue;"
                      "background-color: darkCyan");
    }
    else
    {
        state=true;
        gate->setState(state);
        setStyleSheet("border-width: 2px;"
                      "border-radius: 3px;"
                      "border-style: outset;"
                      "border-color: darkBlue;"
                      "background-color: darkRed");
    }
}
