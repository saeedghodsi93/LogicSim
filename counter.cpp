#include "widget.h"
#include "graphwidget.h"
#include "pin.h"
#include "wire.h"
#include "mainwindow.h"
#include "counter.h"

Counter::Counter()
    : Gate(CounterGate)
{
    QPixmap pixmap;
    pixmap.load("C:/Images/COUNTERICON.PNG");
    inputList << (new Pin(this,QPoint(2,22),InputPin,true));
    outputList << (new Pin(this,QPoint(37,56),OutputPin,true));
    outputList << (new Pin(this,QPoint(63,56),OutputPin,true));
    setPixmap(pixmap);
}

Counter::Counter(bool instantDraw, int bits, int value)
    : Gate(CounterGate)
{
    Widget::simulator()->setDisabled(true);
    number=value;
    numberofbits=0;
    state=false;

    if(instantDraw==true)
    {
        Draw(bits,value);
    }
    else
    {
        m=new MainWindow(this);
        m->show();
    }
}

void Counter::Draw(int bits, int value)
{
    Widget::simulator()->setEnabled(true);
    numberofbits=bits;

    QPixmap pixmap;
    QGraphicsProxyWidget *displayproxy = new QGraphicsProxyWidget(this);
    QGraphicsProxyWidget *resetproxy = new QGraphicsProxyWidget(this);
    switch(numberofbits)
    {
    case 2:
        display=new counterDisplay(this,QPoint(64,20),value);
        resetcounter=new Reset(this,QPoint(64,75));
        pixmap.load("C:/Images/COUNTER2.PNG");
        inputList << (new Pin(this,QPoint(22,65),InputPin,false,0));
        outputList << (new Pin(this,QPoint(118,170),OutputPin,false,0));
        outputList << (new Pin(this,QPoint(190,170),OutputPin,false,1));
        break;

    case 4:
        display=new counterDisplay(this,QPoint(55,22),value);
        resetcounter=new Reset(this,QPoint(55,75));
        pixmap.load("C:/Images/COUNTER4.PNG");
        inputList << (new Pin(this,QPoint(-5,70),InputPin,false,0));
        outputList << (new Pin(this,QPoint(60,170),OutputPin,false,0));
        outputList << (new Pin(this,QPoint(115,170),OutputPin,false,1));
        outputList << (new Pin(this,QPoint(175,170),OutputPin,false,2));
        outputList << (new Pin(this,QPoint(233,170),OutputPin,false,3));
        break;

    case 8:
        display=new counterDisplay(this,QPoint(175,22),value);
        resetcounter=new Reset(this,QPoint(175,75));
        pixmap.load("C:/Images/COUNTER8.PNG");
        inputList << (new Pin(this,QPoint(-5,70),InputPin,false,0));
        outputList << (new Pin(this,QPoint(62,170),OutputPin,false,0));
        outputList << (new Pin(this,QPoint(118,170),OutputPin,false,1));
        outputList << (new Pin(this,QPoint(178,170),OutputPin,false,2));
        outputList << (new Pin(this,QPoint(235,170),OutputPin,false,3));
        outputList << (new Pin(this,QPoint(296,170),OutputPin,false,4));
        outputList << (new Pin(this,QPoint(352,170),OutputPin,false,5));
        outputList << (new Pin(this,QPoint(410,170),OutputPin,false,6));
        outputList << (new Pin(this,QPoint(469,170),OutputPin,false,7));
        break;

    case 16:
        display=new counterDisplay(this,QPoint(400,22),value);
        resetcounter=new Reset(this,QPoint(400,75));
        pixmap.load("C:/Images/COUNTER16.PNG");
        inputList << (new Pin(this,QPoint(-5,70),InputPin,false,0));
        outputList << (new Pin(this,QPoint(60,170),OutputPin,false,0));
        outputList << (new Pin(this,QPoint(117,170),OutputPin,false,1));
        outputList << (new Pin(this,QPoint(177,170),OutputPin,false,2));
        outputList << (new Pin(this,QPoint(232,170),OutputPin,false,3));
        outputList << (new Pin(this,QPoint(295,170),OutputPin,false,4));
        outputList << (new Pin(this,QPoint(350,170),OutputPin,false,5));
        outputList << (new Pin(this,QPoint(410,170),OutputPin,false,6));
        outputList << (new Pin(this,QPoint(467,170),OutputPin,false,7));
        outputList << (new Pin(this,QPoint(524,170),OutputPin,false,8));
        outputList << (new Pin(this,QPoint(580,170),OutputPin,false,9));
        outputList << (new Pin(this,QPoint(640,170),OutputPin,false,10));
        outputList << (new Pin(this,QPoint(696,170),OutputPin,false,11));
        outputList << (new Pin(this,QPoint(758,170),OutputPin,false,12));
        outputList << (new Pin(this,QPoint(813,170),OutputPin,false,13));
        outputList << (new Pin(this,QPoint(873,170),OutputPin,false,14));
        outputList << (new Pin(this,QPoint(930,170),OutputPin,false,15));
        break;

    default:
        display=new counterDisplay(this,QPoint(68,48),value);
        pixmap.load("C:/Images/COUNTER2.PNG");
        inputList << (new Pin(this,QPoint(22,65),InputPin,false,0));
        outputList << (new Pin(this,QPoint(118,170),OutputPin,false,0));
        outputList << (new Pin(this,QPoint(190,170),OutputPin,false,1));
        break;
    }
    setPixmap(pixmap);
    displayproxy->setWidget(display);
    resetproxy->setWidget(resetcounter);
}

void Counter::resetCounter()
{
    number=0;
}

void Counter::inputStateAdjust()
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

void Counter::outputStateAdjust()
{
    //hanooz az mainwindow barnagashte:
    if(numberofbits==0)
        return;

    if(state==true && inputList[0]->getPinState()==false)
    {
        number++;
        if(number >= pow(2,numberofbits))
            number=0;
        display->setnumber(number);

        int tempnumber=number;
        int power = numberofbits-1;
        while(power >= 0)
        {
            if(tempnumber >= pow(2,power))
            {
                tempnumber -= pow(2,power);
                outputList[numberofbits-power-1]->setPinState(true);
            }
            else
            {
                outputList[numberofbits-power-1]->setPinState(false);
            }
            power--;
        }
    }
    state=inputList[0]->getPinState();
}

QList<Pin *> Counter::InputList()
{
    return inputList;
}

QList<Pin *> Counter::OutputList()
{
    return outputList;
}

int Counter::getDisplayValue()
{
    return number;
}

void Counter::setDisplayValue(int value)
{
    number=value;
}

int Counter::getNumberOfBits()
{
    return numberofbits;
}

QVariant Counter::itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant &value)
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

QPainterPath Counter::shape() const
{
    QPainterPath path;
    switch(numberofbits)
    {
    case 2:
    case 4:
        path.addRect(20, 0, 250, 200);
        break;

    case 8:
        path.addRect(20, 0, 480, 200);
        break;

    case 16:
        path.addRect(20, 0, 960, 200);
        break;

    default:
        path.addRect(20, 0, 250, 200);
        break;
    }
    return path;
}

/******************************************************************************************/
/******************************************************************************************/

counterDisplay::counterDisplay(Counter *pargate, QPoint relPosition, int value)
    : gate(pargate),position(relPosition),itemtype(counterdisplay)
{
    setReadOnly(true);

    QFont font = this->font();
    font.setPointSize(font.pointSize() + 20);
    setFont(font);

    setAlignment(Qt::AlignCenter);
    move(position);
    switch(gate->getNumberOfBits())
    {
    case 8:
        resize(QSize(285,50));
        move(position.x()-50,position.y());
        break;

    case 16:
        resize(QSize(425,50));
        move(position.x()-120,position.y());
        break;

    default:
        resize(QSize(185,50));
        break;
    }
    setStyleSheet("border-width: 3px;"
                  "border-radius: 8px;"
                  "border-style: inset;"
                  "border-color: cyan;");

    QString displayedValue;
    displayedValue.setNum(value);
    setText(displayedValue);
}

int counterDisplay::getnumber()
{
    return number;
}

void counterDisplay::setnumber(int num)
{
    QString displayedValue;
    displayedValue.setNum(num);
    setText(displayedValue);
}

itemType counterDisplay::getItemType()
{
    return itemtype;
}

Counter *counterDisplay::parentGate() const
{
    return gate;
}

/******************************************************************************************/
/******************************************************************************************/

Reset::Reset(Counter *pargate, QPoint relPosition)
    : gate(pargate),position(relPosition),itemtype(resetlabel)
{
    setStyleSheet("background-color: white");

    QFont font = this->font();
    font.setPointSize(font.pointSize() + 20);
    setFont(font);

    setAlignment(Qt::AlignCenter);
    move(position);
    resize(QSize(185,50));

    setText("Reset");
}

itemType Reset::getItemType()
{
    return itemtype;
}

Counter *Reset::parentGate() const
{
    return gate;
}

void Reset::mousePressEvent(QMouseEvent *event)
{
    if (!(event->buttons() & Qt::LeftButton))
            return;

    gate->resetCounter();
}
