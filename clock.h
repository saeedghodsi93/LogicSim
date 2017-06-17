#ifndef CLOCK_H
#define CLOCK_H
#include <QApplication>
#include <QLineEdit>

class graphWidget;
class Gate;
class Pin;
class clockDisplay;

class Clock : public Gate
{
public:
    Clock(bool isIcon, int Period= 1000);
    virtual QList<Pin *> OutputList();
    clockDisplay *getDisplay();
    int getPeriod();
    void setPeriod(int per= 1000);

protected:
    QVariant itemChange(GraphicsItemChange change, const QVariant &value);
    QPainterPath shape() const;

private:
    clockDisplay *display;
    int period;

    QList<Pin *> outputList;
};

/******************************************************************************************/
/******************************************************************************************/

class clockDisplay : public QLineEdit
{
public:
    clockDisplay(Clock *pargate= 0,int value= 1000, QPoint relPosition= QPoint(44,35));

    int getnumber();

    enum itemType getItemType();
    Clock *parentGate() const;

protected:
    void keyPressEvent(QKeyEvent *event);
    void timerEvent(QTimerEvent *);

private:
    enum itemType itemtype;
    Clock *gate;
    int number;
    int timerID;
    QPoint position;
};

#endif // CLOCK_H
