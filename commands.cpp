#include <QtWidgets>
#include "widget.h"
#include "graphwidget.h"
#include "gate.h"
#include "clock.h"
#include "userio.h"
#include "numericio.h"
#include "multiplexer.h"
#include "flipflop.h"
#include "counter.h"
#include "commands.h"

MoveCommand::MoveCommand(Gate *movinggate, const QPointF &oldpos, QUndoCommand *parent)
    : QUndoCommand(parent)
{
    gate = movinggate;
    newPos = gate->pos();
    oldPos = oldpos;
}

void MoveCommand::setGate(Gate *movinggate)
{
    gate=movinggate;
}

bool MoveCommand::mergeWith(const QUndoCommand *command)
{
    const MoveCommand *moveCommand = static_cast<const MoveCommand *>(command);
    Gate *tempGate = moveCommand->gate;

    if (gate != tempGate)
        return false;

    newPos = tempGate->pos();
    return true;
}

void MoveCommand::undo()
{
    gate->setPos(oldPos);
    Widget::simulator()->BoardGraph()->scene()->update();
}

void MoveCommand::redo()
{
    gate->setPos(newPos);
}

AddCommand::AddCommand(Gate *addedgate, QUndoCommand *parent)
    : QUndoCommand(parent)
{
    gate=addedgate;
    gatetype=gate->getGateType();
    Widget::simulator()->BoardGraph()->scene()->update();
}

AddCommand::AddCommand(Clock *addedgate, QUndoCommand *parent)
    : QUndoCommand(parent)
{
    clock=addedgate;
    gatetype=clock->getGateType();
    Widget::simulator()->BoardGraph()->scene()->update();
}

AddCommand::AddCommand(UserIO *addedgate, QUndoCommand *parent)
    : QUndoCommand(parent)
{
    userio=addedgate;
    gatetype=userio->getGateType();
    Widget::simulator()->BoardGraph()->scene()->update();
}

AddCommand::AddCommand(NumericIO *addedgate, QUndoCommand *parent)
    : QUndoCommand(parent)
{
    numericio=addedgate;
    gatetype=numericio->getGateType();
    Widget::simulator()->BoardGraph()->scene()->update();
}

AddCommand::AddCommand(Multiplexer *addedgate, QUndoCommand *parent)
    : QUndoCommand(parent)
{
    multiplexer=addedgate;
    gatetype=multiplexer->getGateType();
    Widget::simulator()->BoardGraph()->scene()->update();
}

AddCommand::AddCommand(Flipflop *addedgate, QUndoCommand *parent)
    : QUndoCommand(parent)
{
    flipflop=addedgate;
    gatetype=flipflop->getGateType();
    Widget::simulator()->BoardGraph()->scene()->update();
}

AddCommand::AddCommand(Counter *addedgate, QUndoCommand *parent)
    : QUndoCommand(parent)
{
    counter=addedgate;
    gatetype=counter->getGateType();
    Widget::simulator()->BoardGraph()->scene()->update();
}

void AddCommand::undo()
{
    switch(gatetype)
    {
    case Buffer:
    case Not:
    case And:
    case Or:
    case Nand:
    case Nor:
    case Xor:
    case Xnor:
        Position=gate->pos();
        Widget::simulator()->BoardGraph()->deleteGate(gate);
        gate=0;
        break;

    case ClockGate:
        Position=clock->pos();
        period=clock->getPeriod();
        Widget::simulator()->BoardGraph()->deleteClock(clock);
        clock=0;
        break;

    case UserInput:
    case UserOutput:
        Position=userio->pos();
        state=userio->getState();
        Widget::simulator()->BoardGraph()->deleteUserIO(userio);
        userio=0;
        break;

    case NumericInput:
    case NumericOutput:
        Position=numericio->pos();
        numericbits=numericio->getNumberOfBits();
        value=numericio->getDisplayValue();
        numbase=numericio->getBaseValue();
        Widget::simulator()->BoardGraph()->deleteNumericIO(numericio);
        numericio=0;
        break;

    case MultiPlexer:
        Position=multiplexer->pos();
        multbits=multiplexer->getNumberOfBits();
        Widget::simulator()->BoardGraph()->deleteMultiplexer(multiplexer);
        multiplexer=0;
        break;

    case FlipFlop:
        Position=flipflop->pos();
        Widget::simulator()->BoardGraph()->deleteFlipflop(flipflop);
        flipflop=0;
        break;

    case CounterGate:
        Position=counter->pos();
        counterbits=counter->getNumberOfBits();
        number=counter->getDisplayValue();
        Widget::simulator()->BoardGraph()->deleteCounter(counter);
        counter=0;
        break;

    default:
        break;
    }
    Widget::simulator()->BoardGraph()->scene()->update();
}

void AddCommand::redo()
{
    switch(gatetype)
    {
    case Buffer:
        if(!gate)
        {
            gate=Widget::simulator()->BoardGraph()->addGate(0,Position,true);
            Widget::simulator()->lastMoveCommand()->setGate(gate);
        }
        break;

    case Not:
        if(!gate)
        {
            gate=Widget::simulator()->BoardGraph()->addGate(1,Position,true);
            Widget::simulator()->lastMoveCommand()->setGate(gate);
        }
        break;

    case And:
        if(!gate)
        {
            gate=Widget::simulator()->BoardGraph()->addGate(2,Position,true);
            Widget::simulator()->lastMoveCommand()->setGate(gate);
        }
        break;

    case Or:
        if(!gate)
        {
            gate=Widget::simulator()->BoardGraph()->addGate(3,Position,true);
            Widget::simulator()->lastMoveCommand()->setGate(gate);
        }
        break;

    case Nand:
        if(!gate)
        {
            gate=Widget::simulator()->BoardGraph()->addGate(4,Position,true);
            Widget::simulator()->lastMoveCommand()->setGate(gate);
        }
        break;

    case Nor:
        if(!gate)
        {
            gate=Widget::simulator()->BoardGraph()->addGate(5,Position,true);
            Widget::simulator()->lastMoveCommand()->setGate(gate);
        }
        break;

    case Xor:
        if(!gate)
        {
            gate=Widget::simulator()->BoardGraph()->addGate(6,Position,true);
            Widget::simulator()->lastMoveCommand()->setGate(gate);
        }
        break;

    case Xnor:
        if(!gate)
        {
            gate=Widget::simulator()->BoardGraph()->addGate(7,Position,true);
            Widget::simulator()->lastMoveCommand()->setGate(gate);
        }
        break;

    case ClockGate:
        if(!clock)
        {
            clock=Widget::simulator()->BoardGraph()->addClock(Position,true,period);
            Widget::simulator()->lastMoveCommand()->setGate(clock);
        }
        break;

    case UserInput:
        if(!userio)
        {
            userio=Widget::simulator()->BoardGraph()->addUserIO(9,Position,true,state);
            Widget::simulator()->lastMoveCommand()->setGate(userio);
        }
        break;

    case UserOutput:
        if(!userio)
        {
            userio=Widget::simulator()->BoardGraph()->addUserIO(10,Position,true,state);
            Widget::simulator()->lastMoveCommand()->setGate(userio);
        }
        break;

    case NumericInput:
        if(!numericio)
        {
            numericio=Widget::simulator()->BoardGraph()->addNumericIO(11,Position,true,true,numericbits,value,numbase);
            Widget::simulator()->lastMoveCommand()->setGate(numericio);
        }
        break;

    case NumericOutput:
        if(!numericio)
        {
            numericio=Widget::simulator()->BoardGraph()->addNumericIO(12,Position,true,true,numericbits,value,numbase);
            Widget::simulator()->lastMoveCommand()->setGate(numericio);
        }
        break;

    case MultiPlexer:
        if(!multiplexer)
        {
            multiplexer=Widget::simulator()->BoardGraph()->addMultiplexer(Position,true,true,multbits);
            Widget::simulator()->lastMoveCommand()->setGate(multiplexer);
        }
        break;

    case FlipFlop:
        if(!flipflop)
        {
            flipflop=Widget::simulator()->BoardGraph()->addFlipflop(Position,true);
            Widget::simulator()->lastMoveCommand()->setGate(flipflop);
        }
        break;

    case CounterGate:
        if(!counter)
        {
            counter=Widget::simulator()->BoardGraph()->addCounter(Position,true,true,counterbits,number);
            Widget::simulator()->lastMoveCommand()->setGate(counter);
        }
        break;

    default:
        if(!gate)
        {
            gate=Widget::simulator()->BoardGraph()->addGate(0,Position,true);
            Widget::simulator()->lastMoveCommand()->setGate(gate);
        }
        break;
    }
    Widget::simulator()->BoardGraph()->scene()->update();
}
