#include "graphwidget.h"
#include "gate.h"
#include "pin.h"
#include "clock.h"

Clock::Clock(bool isIcon, int Period)
    : Gate(ClockGate),period(Period)
{
    QPixmap pixmap;
    if(isIcon==true)
    {
        pixmap.load("C:/Images/CLOCKICON.PNG");
        outputList << (new Pin(this,QPoint(95,25),OutputPin,true));
    }
    else
    {
        pixmap.load("C:/Images/CLOCK.PNG");
        QGraphicsProxyWidget *proxy = new QGraphicsProxyWidget(this);
        display = new clockDisplay(this,period,QPoint(44,35));
        proxy->setWidget(display);
        outputList << (new Pin(this,QPoint(300,82),OutputPin,false,0));
    }
    setPixmap(pixmap);
}

QList<Pin *> Clock::OutputList()
{
    return outputList;
}

clockDisplay *Clock::getDisplay()
{
    return display;
}

int Clock::getPeriod()
{
    return period;
}

void Clock::setPeriod(int per)
{
    period=per;
}

QVariant Clock::itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant &value)
{
    switch (change)
    {
    case ItemPositionHasChanged:
        foreach (Pin *pin, outputList)
            pin->positionAdjust();
        break;

    default:
        break;
    };
    return QGraphicsItem::itemChange(change, value);
}

QPainterPath Clock::shape() const
{
    QPainterPath path;
    path.addRect(20, 0, 250, 200);
    return path;
}

/******************************************************************************************/
/******************************************************************************************/

clockDisplay::clockDisplay(Clock *pargate, int value, QPoint relPosition)
    : gate(pargate),position(relPosition),itemtype(clockdisplay)
{
    QFont font = this->font();
    font.setPointSize(font.pointSize() + 20);
    setFont(font);

    setAlignment(Qt::AlignCenter);
    move(position);
    resize(QSize(185,50));
    setStyleSheet("border-width: 3px;"
                  "border-radius: 8px;"
                  "border-style: inset;"
                  "border-color: cyan;");

    QString displayedValue;
    displayedValue.setNum(value);
    setText(displayedValue);
    number=value;

    timerID=startTimer(number);
}

int clockDisplay::getnumber()
{
    return number;
}

itemType clockDisplay::getItemType()
{
    return itemtype;
}

Clock *clockDisplay::parentGate() const
{
    return gate;
}

void clockDisplay::keyPressEvent(QKeyEvent *event)
{
    QLineEdit::keyPressEvent(event);

    number=text().toInt();
    gate->setPeriod(number);

    killTimer(timerID);
    timerID=startTimer(number);
}

void clockDisplay::timerEvent(QTimerEvent *)
{
    gate->OutputList()[0]->toggleState();
}
