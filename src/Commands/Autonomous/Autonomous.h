#pragma once

#include "Commands/CommandGroup.h"

class Autonomous : public CommandGroup {
public:
    Autonomous();
private:
    const float auto_speed = .4f;
    const float auto_time = 3.5f;
};
