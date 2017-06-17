#ifndef NUMERICIO_H
#define NUMERICIO_H
#include <QApplication>
#include <QLineEdit>
#include <QLabel>
#include "gate.h"

class Widget;
class graphWidget;
class Pin;
class Wire;
class numericDisplay;
class Base;
class MainWindow;

enum numericBase{DEC,BIN,OCT,HEX};

class NumericIO : public Gate
{
public:
    NumericIO(gateType type= NumericInput);
    NumericIO(int type, bool instantDraw=false, int bits= 2, int value=0, int numbase= 10);
    void Draw(int bits= 2, int value= 0, numericBase numbase= DEC);

    virtual void inputStateAdjust();
    virtual void outputStateAdjust();
    virtual QList<Pin *> InputList();
    virtual QList<Pin *> OutputList();
    numericDisplay *getDisplay();
    Base *getBase();
    int getDisplayValue();
    void setDisplayValue(int value);
    int getBaseValue();
    void setBaseValue(int value);
    int getNumberOfBits();

protected:
    QVariant itemChange(GraphicsItemChange change, const QVariant &value);
    QPainterPath shape() const;

private:
    numericDisplay *display;
    Base *base;
    MainWindow *m;
    int displayvalue;
    int basevalue;
    int numberofbits;

    QList<Pin *> inputList;
    QList<Pin *> outputList;
};

/******************************************************************************************/
/******************************************************************************************/

class numericDisplay : public QLineEdit
{
public:
    numericDisplay(NumericIO *pargate= 0, QPoint relPosition= QPoint(44,35), int value= 0);
    void updateBase(int newbase);

    int getnumber();
    void setnumber(int num);

    enum itemType getItemType();
    NumericIO *parentGate() const;

protected:
    void keyPressEvent(QKeyEvent *event);

private:
    enum itemType itemtype;
    NumericIO *gate;
    int number;
    QPoint position;
};

/******************************************************************************************/
/******************************************************************************************/

class Base : public QLabel
{
public:
    Base(NumericIO *pargate= 0, QPoint relPosition= QPoint(44,35), numericBase numbase= DEC);
    int getNumericBase();

    enum itemType getItemType();
    NumericIO *parentGate() const;

protected:
    void mousePressEvent(QMouseEvent *event);

private:
    enum itemType itemtype;
    enum numericBase numericbase;
    NumericIO *gate;
    QPoint position;
};

#endif // NUMERICIO_H
