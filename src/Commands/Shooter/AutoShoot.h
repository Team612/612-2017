#pragma once


#include "Commands/Command.h"
#include "../../Robot.h"
//This command runs the shooter at OPTIMAL_RPM for a time specified in the constructor. No input required.
class AutoShoot: public Command {
public:
    AutoShoot(double timeout);

    virtual void Initialize();
    virtual void Execute();
    virtual bool IsFinished();
    virtual void End();
    virtual void Interrupted();

private:
    double OPTIMAL_RPM = 3200;
    double timeout;
};
