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
    const float OPTIMAL_RPM = -3300.0f;
    const float THROTTLE = 500.0f;
    const float IDLE = 1000.0f;
    const float START_MULTIPLIER = 1.25f;
    const double DEADBAND = 0.01;
};
