#pragma once

#include "Commands/Command.h"

class ToggleGear: public Command {
public:
    ToggleGear();

    void Initialize() override;
    bool IsFinished() override;
};

