#pragma once

#include "WPILib.h"

class SetIntake: public Command {
    bool clear;
public:
    SetIntake(bool clear = false);

    void Initialize() override;
    void Execute() override;
    bool IsFinished() override;
    void End() override;
    void Interrupted() override;
};
