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
    const double OPTIMAL_RPM = -3600;
    double IDLE = 1000;
    const float START_MULTIPLIER = 1.25;
};
