#pragma once

#include "Commands/Command.h"
#include "../../Robot.h"

class Grab: public Command {
public:
    Grab();

    virtual void Initialize();
    virtual void Execute();
    virtual bool IsFinished();
    virtual void End();
    virtual void Interrupted();
private:
    const double CURRENT_THRESHOLD = 2; //TODO replace with a number that make sense
};
