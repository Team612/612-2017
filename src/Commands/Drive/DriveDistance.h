#pragma once

#include "Commands/Subsystem.h"
#include "../../Robot.h"

class DriveDistance: public Command {
public:
    DriveDistance(double distance);

    virtual void Initialize();
    virtual void Execute();
    virtual bool IsFinished();
    virtual void End();
    virtual void Interrupted();

private:
    final double SPEED; //A constant determining speed
    double distance;
    double leftInitialDistance;
    double rightInitialDistance;
};
