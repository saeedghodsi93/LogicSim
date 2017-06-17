#ifndef COMMANDS_H
#define COMMANDS_H
#include <QUndoCommand>
#include <QPointF>

class Widget;
class graphWidget;
class Gate;
class Clock;
class UserIO;
class NumericIO;
class Multiplexer;
class Flipflop;
class Counter;

class MoveCommand : public QUndoCommand
{
public:
    MoveCommand(Gate *movinggate, const QPointF &oldpos, QUndoCommand *parent = 0);
    void setGate(Gate *movinggate);

    void undo();
    void redo();
    bool mergeWith(const QUndoCommand *command);

private:
    Gate *gate;
    QPointF oldPos;
    QPointF newPos;
};

class AddCommand : public QUndoCommand
{
public:
    AddCommand(Gate *addedgate, QUndoCommand *parent = 0);
    AddCommand(Clock *addedgate, QUndoCommand *parent = 0);
    AddCommand(UserIO *addedgate, QUndoCommand *parent = 0);
    AddCommand(NumericIO *addedgate, QUndoCommand *parent = 0);
    AddCommand(Multiplexer *addedgate, QUndoCommand *parent = 0);
    AddCommand(Flipflop *addedgate, QUndoCommand *parent = 0);
    AddCommand(Counter *addedgate, QUndoCommand *parent = 0);
    void undo();
    void redo();

private:
    Gate *gate;
    Clock *clock;
    int period;
    UserIO *userio;
    bool state;
    NumericIO *numericio;
    int numericbits;
    int value;
    int numbase;
    Multiplexer *multiplexer;
    int multbits;
    Flipflop *flipflop;
    Counter *counter;
    int counterbits;
    int number;
    gateType gatetype;
    QPointF Position;
};

#endif // COMMANDS_H
