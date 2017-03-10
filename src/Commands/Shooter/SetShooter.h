#pragma once

#include "WPILib.h"

class SetShooter : public Command {
public:
    SetShooter(double speed);

    virtual void Initialize();
    virtual void Execute();
    virtual bool IsFinished();
    virtual void End();
    virtual void Interrupted();

private:
    const double OPTIMAL_RPM = 3200;
    const double IDLE = OPTIMAL_RPM / 10;
    double speed;
};
