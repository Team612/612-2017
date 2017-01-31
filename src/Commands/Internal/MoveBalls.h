#pragma once

#include "Commands/Command.h"
#include "../../Robot.h"

class MoveBalls: public Command {
public:
    MoveBalls();

    virtual void Initialize();
    virtual void Execute();
    virtual bool IsFinished();
    virtual void End();
    virtual void Interrupted();

private:

};
