#pragma once

#include "Commands/CommandGroup.h"
#include "RobotMap.h"

class Autonomous : public CommandGroup {
public:
    Autonomous(std::string AUTOCOMMAND);
};
