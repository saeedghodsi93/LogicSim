#ifndef COUNTER_H
#define COUNTER_H
#include <QApplication>
#include <QLineEdit>
#include <QLabel>
#include "gate.h"

class Widget;
class graphWidget;
class Pin;
class Wire;
class counterDisplay;
class Reset;
class MainWindow;

class Counter : public Gate
{
public:
    Counter();
    Counter(bool instantDraw, int bits= 2, int value=0);
    void Draw(int bits= 2, int value= 0);
    void resetCounter();

    virtual void inputStateAdjust();
    virtual void outputStateAdjust();
    virtual QList<Pin *> InputList();
    virtual QList<Pin *> OutputList();
    int getDisplayValue();
    void setDisplayValue(int value);
    int getNumberOfBits();

protected:
    QVariant itemChange(GraphicsItemChange change, const QVariant &value);
    QPainterPath shape() const;

private:
    counterDisplay *display;
    Reset *resetcounter;
    MainWindow *m;
    int number;
    int numberofbits;
    bool state;

    QList<Pin *> inputList;
    QList<Pin *> outputList;
};

/******************************************************************************************/
/******************************************************************************************/

class counterDisplay : public QLineEdit
{
public:
    counterDisplay(Counter *pargate= 0, QPoint relPosition= QPoint(44,35), int value= 0);

    enum itemType getItemType();
    Counter *parentGate() const;

    int getnumber();
    void setnumber(int num);

private:
    enum itemType itemtype;
    Counter *gate;
    int number;
    QPoint position;
};

/******************************************************************************************/
/******************************************************************************************/

class Reset : public QLabel
{
public:
    Reset(Counter *pargate= 0, QPoint relPosition= QPoint(44,35));

    enum itemType getItemType();
    Counter *parentGate() const;

protected:
    void mousePressEvent(QMouseEvent *event);

private:
    enum itemType itemtype;
    Counter *gate;
    QPoint position;
};

#endif // COUNTER_H
