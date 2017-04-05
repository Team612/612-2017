#pragma once

#include "Commands/Subsystem.h"
#include "../RobotMap.h"

class Climber: public Subsystem {
private:
public:
    Climber();
    void InitDefaultCommand();
    void Move(float speed); //drive climber at speed
    void Block();
};
