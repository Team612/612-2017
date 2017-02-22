#pragma once

#include "WPILib.h"
#include "Commands/Command.h"
#include "../../Robot.h"

class AutoIntake: public Command {
public:
    AutoIntake(double timeout);
    void Initialize() override;
    void Execute() override;
    bool IsFinished() override;
    void End() override;
    void Interrupted() override;
private:
    double timeout;
};
