#pragma once

#include "Commands/Command.h"
#include "Subsystems/GearSystem.h"

class ToggleGear: public Command {
    GearState state;
public:
    ToggleGear(GearState set_state);

    void Initialize() override;
    bool IsFinished() override;
};

