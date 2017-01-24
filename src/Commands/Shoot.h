#pragma once


#include "Commands/Command.h"
#include "../Robot.h"

class Shoot: public Command {
public:
    Shoot();

    virtual void Initialize();
    virtual void Execute();
    virtual bool IsFinished();
    virtual void End();
    virtual void Interrupted();

private:

};
