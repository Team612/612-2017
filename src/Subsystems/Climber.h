#pragma once

#include "Commands/Subsystem.h"
#include "../RobotMap.h"
#include "WPILib.h"

class Climber: public Subsystem {
private:
public:
    Climber();
    void InitDefaultCommand();
    void Move(float speed); //drive climber at speed
    void Block();
    void Grab(double position);
};
