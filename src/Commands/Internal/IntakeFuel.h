#pragma once

#include "WPILib.h"
#include "Commands/Command.h"
#include "../../Robot.h"

class IntakeFuel: public Command {
public:
    IntakeFuel();
    void Initialize() override;
    void Execute() override;
    bool IsFinished() override;
    void End() override;
    void Interrupted() override;
private:
    //bool in;
};
