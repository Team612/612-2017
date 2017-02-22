#pragma once

#include "Commands/Subsystem.h"
#include "../../Robot.h"

class DriveDistance: public PIDCommand {
public:
    DriveDistance(double distance);

    virtual void Initialize();
    virtual void Execute();
    virtual bool IsFinished();
    virtual void End();
    virtual void Interrupted();
    virtual double ReturnPIDInput();
    virtual void UsePIDOutput(double output);

private:
    double pi = 3.141592653;

    double MAX_THROTTLE = 0.75; //A constant determining speed, 0 to 1
    double distance; //Encoder units; converted from meters in constructor
    double leftInitialDistance;
    double rightInitialDistance;
};
