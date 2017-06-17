#ifndef MULTIPLEXER_H
#define MULTIPLEXER_H
#include <QApplication>
#include "gate.h"

class Widget;
class graphWidget;
class Pin;
class Wire;
class MainWindow;

class Multiplexer : public Gate
{
public:
    Multiplexer();
    Multiplexer(bool instantDraw, int bits= 2);
    void Draw(int bits= 2);

    virtual void inputStateAdjust();
    virtual void outputStateAdjust();
    virtual QList<Pin *> InputList();
    virtual QList<Pin *> OutputList();
    int getNumberOfBits();

protected:
    QVariant itemChange(GraphicsItemChange change, const QVariant &value);
    QPainterPath shape() const;

private:
    MainWindow *m;
    int numberofbits;

    QList<Pin *> inputList;
    QList<Pin *> outputList;
};

#endif // MULTIPLEXER_H
