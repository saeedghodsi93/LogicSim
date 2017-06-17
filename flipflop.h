#ifndef FLIPFLOP_H
#define FLIPFLOP_H
#include <QApplication>
#include "gate.h"

class Widget;
class graphWidget;
class Pin;
class Wire;

class Flipflop : public Gate
{
public:
    Flipflop(bool isIcon= true);

    virtual void inputStateAdjust();
    virtual void outputStateAdjust();
    virtual QList<Pin *> InputList();
    virtual QList<Pin *> OutputList();

protected:
    QVariant itemChange(GraphicsItemChange change, const QVariant &value);
    QPainterPath shape() const;

private:
    bool state;
    QList<Pin *> inputList;
    QList<Pin *> outputList;
};

#endif // FLIPFLOP_H
