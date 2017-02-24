#pragma once


#include "Commands/Command.h"
#include "../../Robot.h"

class Shoot: public Command {
public:
    Shoot();

    virtual void Initialize();
    virtual void Execute();
    virtual bool IsFinished();
    virtual void End();
    virtual void Interrupted();

private:
    double OPTIMAL_RPM = 3200;
    double IDLE = OPTIMAL_RPM / 10;
};
