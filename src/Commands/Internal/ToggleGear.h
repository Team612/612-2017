#pragma once

#include "Commands/Command.h"
#include "Subsystems/GearSystem.h"

class ToggleGear: public Command {
public:
    ToggleGear();
    void Initialize() override;
    bool IsFinished() override;
};
