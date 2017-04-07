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
    double speed;
};
