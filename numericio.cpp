#include "widget.h"
#include "graphwidget.h"
#include "pin.h"
#include "wire.h"
#include "mainwindow.h"
#include "numericio.h"

NumericIO::NumericIO(gateType type)
    : Gate(type)
{
    QPixmap pixmap;
    switch(type)
    {
    case NumericInput:
        pixmap.load("C:/Images/NUMERICINPUTICON.PNG");
        outputList << (new Pin(this,QPoint(37,57),OutputPin,true));
        outputList << (new Pin(this,QPoint(63,57),OutputPin,true));
        break;

    case NumericOutput:
        pixmap.load("C:/Images/NUMERICOUTPUTICON.PNG");
        inputList << (new Pin(this,QPoint(37,-5),InputPin,true));
        inputList << (new Pin(this,QPoint(63,-5),InputPin,true));
        break;

    default:
        break;
    }
    setPixmap(pixmap);
}

NumericIO::NumericIO(int type, bool instantDraw, int bits, int value, int numbase)
    : Gate(type)
{
    Widget::simulator()->setDisabled(true);
    numberofbits=0;

    if(instantDraw==true)
    {
        switch(numbase)
        {
        case 10:
            Draw(bits,value,DEC);
            break;

        case 2:
            Draw(bits,value,BIN);
             break;

        case 8:
            Draw(bits,value,OCT);
            break;

        case 16:
            Draw(bits,value,HEX);
            break;

        default:
            Draw(bits,value,DEC);
            break;
        }
    }
    else
    {
        m=new MainWindow(this);
        m->show();
    }
}

void NumericIO::Draw(int bits, int value, numericBase numbase)
{
    Widget::simulator()->setEnabled(true);
    numberofbits=bits;

    QPixmap pixmap;
    QGraphicsProxyWidget *displayproxy = new QGraphicsProxyWidget(this);
    QGraphicsProxyWidget *baseproxy = new QGraphicsProxyWidget(this);
    switch(getGateType())
    {
    case NumericInput:
        switch(numberofbits)
        {
        case 2:
            display=new numericDisplay(this,QPoint(64,20),value);
            base=new Base(this,QPoint(64,75),numbase);
            pixmap.load("C:/Images/NUMERICINPUT2.PNG");
            outputList << (new Pin(this,QPoint(118,170),OutputPin,false,0));
            outputList << (new Pin(this,QPoint(190,170),OutputPin,false,1));
            break;

        case 4:
            display=new numericDisplay(this,QPoint(55,22),value);
            base=new Base(this,QPoint(55,75),numbase);
            pixmap.load("C:/Images/NUMERICINPUT4.PNG");
            outputList << (new Pin(this,QPoint(60,170),OutputPin,false,0));
            outputList << (new Pin(this,QPoint(115,170),OutputPin,false,1));
            outputList << (new Pin(this,QPoint(175,170),OutputPin,false,2));
            outputList << (new Pin(this,QPoint(233,170),OutputPin,false,3));
            break;

        case 8:
            display=new numericDisplay(this,QPoint(175,22),value);
            base=new Base(this,QPoint(175,75),numbase);
            pixmap.load("C:/Images/NUMERICINPUT8.PNG");
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
            display=new numericDisplay(this,QPoint(400,22),value);
            base=new Base(this,QPoint(400,75),numbase);
            pixmap.load("C:/Images/NUMERICINPUT16.PNG");
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
            display=new numericDisplay(this,QPoint(64,20),value);
            base=new Base(this,QPoint(64,75),numbase);
            pixmap.load("C:/Images/NUMERICINPUT2.PNG");
            outputList << (new Pin(this,QPoint(118,170),OutputPin,false,0));
            outputList << (new Pin(this,QPoint(190,170),OutputPin,false,1));
            break;
        }
        break;

    case NumericOutput:
        switch(numberofbits)
        {
        case 2:
            display=new numericDisplay(this,QPoint(68,48),value);
            base=new Base(this,QPoint(68,100),numbase);
            pixmap.load("C:/Images/NUMERICOUTPUT2.PNG");
            inputList << (new Pin(this,QPoint(123,-5),InputPin,false,0));
            inputList << (new Pin(this,QPoint(194,-5),InputPin,false,1));
            break;

        case 4:
            display=new numericDisplay(this,QPoint(53,48),value);
            base=new Base(this,QPoint(53,100),numbase);
            pixmap.load("C:/Images/NUMERICOUTPUT4.PNG");
            inputList << (new Pin(this,QPoint(60,-5),InputPin,false,0));
            inputList << (new Pin(this,QPoint(115,-5),InputPin,false,1));
            inputList << (new Pin(this,QPoint(175,-5),InputPin,false,2));
            inputList << (new Pin(this,QPoint(230,-5),InputPin,false,3));
            break;

        case 8:
            display=new numericDisplay(this,QPoint(175,48),value);
            base=new Base(this,QPoint(175,100),numbase);
            pixmap.load("C:/Images/NUMERICOUTPUT8.PNG");
            inputList << (new Pin(this,QPoint(60,-5),InputPin,false,0));
            inputList << (new Pin(this,QPoint(115,-5),InputPin,false,1));
            inputList << (new Pin(this,QPoint(175,-5),InputPin,false,2));
            inputList << (new Pin(this,QPoint(230,-5),InputPin,false,3));
            inputList << (new Pin(this,QPoint(292,-5),InputPin,false,4));
            inputList << (new Pin(this,QPoint(347,-5),InputPin,false,5));
            inputList << (new Pin(this,QPoint(407,-5),InputPin,false,6));
            inputList << (new Pin(this,QPoint(462,-5),InputPin,false,7));
            break;

        case 16:
            display=new numericDisplay(this,QPoint(400,48),value);
            base=new Base(this,QPoint(400,100),numbase);
            pixmap.load("C:/Images/NUMERICOUTPUT16.PNG");
            inputList << (new Pin(this,QPoint(60,-5),InputPin,false,0));
            inputList << (new Pin(this,QPoint(115,-5),InputPin,false,1));
            inputList << (new Pin(this,QPoint(175,-5),InputPin,false,2));
            inputList << (new Pin(this,QPoint(230,-5),InputPin,false,3));
            inputList << (new Pin(this,QPoint(292,-5),InputPin,false,4));
            inputList << (new Pin(this,QPoint(347,-5),InputPin,false,5));
            inputList << (new Pin(this,QPoint(407,-5),InputPin,false,6));
            inputList << (new Pin(this,QPoint(462,-5),InputPin,false,7));
            inputList << (new Pin(this,QPoint(520,-5),InputPin,false,8));
            inputList << (new Pin(this,QPoint(577,-5),InputPin,false,9));
            inputList << (new Pin(this,QPoint(637,-5),InputPin,false,10));
            inputList << (new Pin(this,QPoint(692,-5),InputPin,false,11));
            inputList << (new Pin(this,QPoint(755,-5),InputPin,false,12));
            inputList << (new Pin(this,QPoint(810,-5),InputPin,false,13));
            inputList << (new Pin(this,QPoint(870,-5),InputPin,false,14));
            inputList << (new Pin(this,QPoint(927,-5),InputPin,false,15));
            break;

        default:
            display=new numericDisplay(this,QPoint(68,48),value);
            base=new Base(this,QPoint(68,100),numbase);
            pixmap.load("C:/Images/NUMERICOUTPUT2.PNG");
            inputList << (new Pin(this,QPoint(123,-5),InputPin,false,0));
            inputList << (new Pin(this,QPoint(194,-5),InputPin,false,1));
            break;
        }
        break;

    default:
        break;
    }
    setPixmap(pixmap);
    displayproxy->setWidget(display);
    baseproxy->setWidget(base);
}

void NumericIO::inputStateAdjust()
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

void NumericIO::outputStateAdjust()
{
    //hanooz az mainwindow bar nagashte:
    if(numberofbits==0)
        return;

    switch(getGateType())
    {
    case NumericInput:
    {
        int number = display->getnumber();
        while(number >= pow(2,numberofbits))
            number -= pow(2,numberofbits);
        int power = numberofbits-1;
        while(power >= 0)
        {
            if(number >= pow(2,power))
            {
                number -= pow(2,power);
                outputList[numberofbits-power-1]->setPinState(true);
            }
            else
            {
                outputList[numberofbits-power-1]->setPinState(false);
            }
            power--;
        }
    }
        break;

    case NumericOutput:
    {
        int number = 0;
        int power = numberofbits-1;
        while(power >= 0)
        {
            if(inputList[numberofbits-power-1]->getPinState() == true)
            {
                number += pow(2,power);
            }
            power--;
        }
        display->setnumber(number);
    }
        break;

    default:
        break;
    }
}

QList<Pin *> NumericIO::InputList()
{
    return inputList;
}

QList<Pin *> NumericIO::OutputList()
{
    return outputList;
}

numericDisplay *NumericIO::getDisplay()
{
    return display;
}

Base *NumericIO::getBase()
{
    return base;
}

int NumericIO::getDisplayValue()
{
    return displayvalue;
}

void NumericIO::setDisplayValue(int value)
{
    displayvalue=value;
}

int NumericIO::getBaseValue()
{
    return basevalue;
}

void NumericIO::setBaseValue(int value)
{
    basevalue=value;
}

int NumericIO::getNumberOfBits()
{
    return numberofbits;
}

QVariant NumericIO::itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant &value)
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

QPainterPath NumericIO::shape() const
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

numericDisplay::numericDisplay(NumericIO *pargate, QPoint relPosition, int value)
    : gate(pargate),position(relPosition),itemtype(numericdisplay)
{
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
    number=value;
    gate->setDisplayValue(number);

    if(gate->getGateType()==NumericOutput)
        setReadOnly(true);
}

void numericDisplay::updateBase(int newbase)
{
    if(gate->getGateType()==NumericInput)
    {
        bool ok;
        number=text().toInt(&ok,newbase);
        gate->setDisplayValue(number);
    }

    if(gate->getGateType()==NumericOutput)
    {
        QString temp;
        temp.setNum(number,newbase);
        setText(temp);
    }
}

int numericDisplay::getnumber()
{
    return number;
}

void numericDisplay::setnumber(int num)
{
    number=num;
    int numericbase=gate->getBase()->getNumericBase();
    QString temp;
    temp.setNum(number,numericbase);
    setText(temp);
}

itemType numericDisplay::getItemType()
{
    return itemtype;
}

NumericIO *numericDisplay::parentGate() const
{
    return gate;
}

void numericDisplay::keyPressEvent(QKeyEvent *event)
{
    QLineEdit::keyPressEvent(event);

    if(gate->getGateType()==NumericInput)
    {
        int numericbase=gate->getBase()->getNumericBase();
        bool ok;
        number=text().toInt(&ok,numericbase);
        gate->setDisplayValue(number);
    }
}

/******************************************************************************************/
/******************************************************************************************/

Base::Base(NumericIO *pargate, QPoint relPosition, numericBase numbase)
    : gate(pargate),position(relPosition),itemtype(base),numericbase(numbase)
{
    switch(numericbase)
    {
    case DEC:
        setText("DEC");
        break;

    case BIN:
        setText("BIN");
        break;

    case OCT:
        setText("OCT");
        break;

    case HEX:
        setText("HEX");
        break;

    default:
        break;
    }

    gate->setBaseValue(getNumericBase());
    setStyleSheet("background-color: white");

    QFont font = this->font();
    font.setPointSize(font.pointSize() + 20);
    setFont(font);

    setAlignment(Qt::AlignCenter);
    move(position);
    resize(QSize(185,50));
}

int Base::getNumericBase()
{
    switch(numericbase)
    {
    case DEC:
        return 10;
        break;

    case BIN:
        return 2;
        break;

    case OCT:
        return 8;
        break;

    case HEX:
        return 16;
        break;

    default:
        return 10;
        break;
    }
}

itemType Base::getItemType()
{
    return itemtype;
}

NumericIO *Base::parentGate() const
{
    return gate;
}

void Base::mousePressEvent(QMouseEvent *event)
{
    if (!(event->buttons() & Qt::LeftButton))
            return;

    switch(numericbase)
    {
    case DEC:
        numericbase=BIN;
        gate->setBaseValue(getNumericBase());
        setText("BIN");
        break;

    case BIN:
        numericbase=OCT;
        gate->setBaseValue(getNumericBase());
        setText("OCT");
        break;

    case OCT:
        numericbase=HEX;
        gate->setBaseValue(getNumericBase());
        setText("HEX");
        break;

    case HEX:
        numericbase=DEC;
        gate->setBaseValue(getNumericBase());
        setText("DEC");
        break;

    default:
        break;
    }
    gate->getDisplay()->updateBase(getNumericBase());
}
