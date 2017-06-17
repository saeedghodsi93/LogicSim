#include "widget.h"
#include "graphwidget.h"
#include "pin.h"
#include "wire.h"
#include "mainwindow.h"
#include "multiplexer.h"

Multiplexer::Multiplexer()
    : Gate(MultiPlexer)
{
    QPixmap pixmap;
    pixmap.load("C:/Images/MULTIPLEXERICON.PNG");
    inputList << (new Pin(this,QPoint(5,28),OutputPin,true));
    inputList << (new Pin(this,QPoint(37,-3),OutputPin,true));
    inputList << (new Pin(this,QPoint(61,-3),OutputPin,true));
    outputList << (new Pin(this,QPoint(95,28),OutputPin,true));
    setPixmap(pixmap);
}

Multiplexer::Multiplexer(bool instantDraw, int bits)
    : Gate(MultiPlexer)
{
    Widget::simulator()->setDisabled(true);
    numberofbits=0;
    if(instantDraw==true)
    {
        Draw(bits);
    }
    else
    {
        m=new MainWindow(this);
        m->show();
    }
}

void Multiplexer::Draw(int bits)
{
    Widget::simulator()->setEnabled(true);
    numberofbits=bits;

    QPixmap pixmap;
    switch(numberofbits)
    {
    case 2:
        pixmap.load("C:/Images/MULTIPLEXER2.PNG");
        inputList << (new Pin(this,QPoint(27,95),InputPin,false,0));
        inputList << (new Pin(this,QPoint(122,5),InputPin,false,1));
        inputList << (new Pin(this,QPoint(194,5),InputPin,false,2));
        outputList << (new Pin(this,QPoint(295,95),OutputPin,false,0));
        break;

    case 4:
        pixmap.load("C:/Images/MULTIPLEXER4.PNG");
        inputList << (new Pin(this,QPoint(-5,60),InputPin,false,0));
        inputList << (new Pin(this,QPoint(-5,125),InputPin,false,1));
        inputList << (new Pin(this,QPoint(60,5),InputPin,false,2));
        inputList << (new Pin(this,QPoint(115,5),InputPin,false,3));
        inputList << (new Pin(this,QPoint(175,5),InputPin,false,4));
        inputList << (new Pin(this,QPoint(230,5),InputPin,false,5));
        outputList << (new Pin(this,QPoint(300,85),OutputPin,false,0));
        break;

    case 8:
        pixmap.load("C:/Images/MULTIPLEXER8.PNG");
        inputList << (new Pin(this,QPoint(-5,50),InputPin,false,0));
        inputList << (new Pin(this,QPoint(-5,104),InputPin,false,1));
        inputList << (new Pin(this,QPoint(-5,158),InputPin,false,2));
        inputList << (new Pin(this,QPoint(60,5),InputPin,false,3));
        inputList << (new Pin(this,QPoint(115,5),InputPin,false,4));
        inputList << (new Pin(this,QPoint(175,5),InputPin,false,5));
        inputList << (new Pin(this,QPoint(230,5),InputPin,false,6));
        inputList << (new Pin(this,QPoint(290,5),InputPin,false,7));
        inputList << (new Pin(this,QPoint(348,5),InputPin,false,8));
        inputList << (new Pin(this,QPoint(406,5),InputPin,false,9));
        inputList << (new Pin(this,QPoint(463,5),InputPin,false,10));
        outputList << (new Pin(this,QPoint(530,107),OutputPin,false,0));
        break;

    case 16:
        pixmap.load("C:/Images/MULTIPLEXER16.PNG");
        inputList << (new Pin(this,QPoint(-5,55),InputPin,false,0));
        inputList << (new Pin(this,QPoint(-5,105),InputPin,false,1));
        inputList << (new Pin(this,QPoint(-5,175),InputPin,false,2));
        inputList << (new Pin(this,QPoint(-5,228),InputPin,false,3));
        inputList << (new Pin(this,QPoint(60,5),InputPin,false,4));
        inputList << (new Pin(this,QPoint(115,5),InputPin,false,5));
        inputList << (new Pin(this,QPoint(175,5),InputPin,false,6));
        inputList << (new Pin(this,QPoint(230,5),InputPin,false,7));
        inputList << (new Pin(this,QPoint(290,5),InputPin,false,8));
        inputList << (new Pin(this,QPoint(348,5),InputPin,false,9));
        inputList << (new Pin(this,QPoint(406,5),InputPin,false,10));
        inputList << (new Pin(this,QPoint(463,5),InputPin,false,11));
        inputList << (new Pin(this,QPoint(520,5),InputPin,false,12));
        inputList << (new Pin(this,QPoint(580,5),InputPin,false,13));
        inputList << (new Pin(this,QPoint(637,5),InputPin,false,14));
        inputList << (new Pin(this,QPoint(695,5),InputPin,false,15));
        inputList << (new Pin(this,QPoint(755,5),InputPin,false,16));
        inputList << (new Pin(this,QPoint(810,5),InputPin,false,17));
        inputList << (new Pin(this,QPoint(870,5),InputPin,false,18));
        inputList << (new Pin(this,QPoint(927,5),InputPin,false,19));
        outputList << (new Pin(this,QPoint(990,140),OutputPin,false,0));
        break;

    default:
        pixmap.load("C:/Images/MULTIPLEXER2.PNG");
        inputList << (new Pin(this,QPoint(27,95),InputPin,false,0));
        inputList << (new Pin(this,QPoint(122,5),InputPin,false,1));
        inputList << (new Pin(this,QPoint(194,5),InputPin,false,2));
        outputList << (new Pin(this,QPoint(295,95),OutputPin,false,0));
        break;
    }
    setPixmap(pixmap);
}

void Multiplexer::inputStateAdjust()
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

void Multiplexer::outputStateAdjust()
{
    switch(numberofbits)
    {
    case 2:
    {
        int number = 0;
        int power = 0;
        while(power >= 0)
        {
            if(inputList[power]->getPinState() == true)
            {
                number += pow(2,power);
            }
            power--;
        }
        outputList[0]->setPinState(inputList[2-number]->getPinState());
    }
        break;

    case 4:
    {
        int number = 0;
        int power = 1;
        while(power >= 0)
        {
            if(inputList[power]->getPinState() == true)
            {
                number += pow(2,power);
            }
            power--;
        }
        outputList[0]->setPinState(inputList[5-number]->getPinState());
    }
        break;

    case 8:
    {
        int number = 0;
        int power = 2;
        while(power >= 0)
        {
            if(inputList[power]->getPinState() == true)
            {
                number += pow(2,power);
            }
            power--;
        }
        outputList[0]->setPinState(inputList[10-number]->getPinState());
    }
        break;

    case 16:
    {
        int number = 0;
        int power = 3;
        while(power >= 0)
        {
            if(inputList[power]->getPinState() == true)
            {
                number += pow(2,power);
            }
            power--;
        }
        outputList[0]->setPinState(inputList[19-number]->getPinState());
    }
        break;

    //ta zamani ke az mainwindow bar nagashte(gate tashkil nashode)varede inja mishe:
    default:
        break;
    }
}

QList<Pin *> Multiplexer::InputList()
{
    return inputList;
}

QList<Pin *> Multiplexer::OutputList()
{
    return outputList;
}

int Multiplexer::getNumberOfBits()
{
    return numberofbits;
}

QVariant Multiplexer::itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant &value)
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

QPainterPath Multiplexer::shape() const
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
