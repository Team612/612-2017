#pragma once


#include "Commands/Command.h"
#include "../../Robot.h"
// A duplicate of Shoot() which does not require user input, for use during Autonomous.
// Proposed function: Shoot until the container is empty
class AutoShoot: public Command {
public:
    AutoShoot();

    virtual void Initialize();
    virtual void Execute();
    virtual bool IsFinished();
    virtual void End();
    virtual void Interrupted();

private:

};
