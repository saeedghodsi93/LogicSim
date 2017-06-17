#ifndef USERIO_H
#define USERIO_H
#include <QApplication>
#include <QLabel>

class graphWidget;
class Gate;
class Pin;
class Wire;
class Label;

enum labelType{InputLabel,OutputLabel};

class UserIO : public Gate
{
public:
    UserIO(gateType type= UserInput);
    UserIO(int type, bool st= false);
    virtual void inputStateAdjust();
    virtual void outputStateAdjust();
    virtual QList<Pin *> InputList();
    virtual QList<Pin *> OutputList();
    bool getState();
    void setState(bool st);

protected:
    QVariant itemChange(GraphicsItemChange change, const QVariant &value);
    QPainterPath shape() const;

private:
    Label *label;
    bool state;

    QList<Pin *> inputList;
    QList<Pin *> outputList;
};

/******************************************************************************************/
/******************************************************************************************/

class Label : public QLabel
{
public:
    Label(UserIO *pargate= 0,bool labelState= false, QPoint relPosition= QPoint(44,30), labelType type= InputLabel);
    void setLabelState();
    bool getLabelState();

    enum itemType getItemType();
    UserIO *parentGate() const;

protected:
    void mousePressEvent(QMouseEvent *event);

private:
    void toggleState();

    enum itemType itemtype;
    enum labelType labeltype;
    bool state;
    UserIO *gate;
    QPoint position;
};

#endif // USREIO_H
