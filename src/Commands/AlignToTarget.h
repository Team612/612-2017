#pragma once

#include "Commands/Command.h"
#include "../Robot.h"

class AlignToTarget: public Command {
public:
    AlignToTarget();

    virtual void Initialize();
    virtual void Execute();
    virtual bool IsFinished();
    virtual void End();
    virtual void Interrupted();

private:

};
