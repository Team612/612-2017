#pragma once

#include "Commands/Subsystem.h"
#include "../RobotMap.h"
#include "WPILib.h"


class Climber: public Subsystem {
private:
public:
    Climber();
    void InitDefaultCommand();
    void Climb(float speed); //drive climber at speed
};
