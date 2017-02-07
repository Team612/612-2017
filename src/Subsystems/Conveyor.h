#pragma once

#include "Commands/Subsystem.h"
#include "../RobotMap.h"
#include "WPILib.h"

class Conveyor: public Subsystem {
private:

public:
    Conveyor();
    void Move(float speed); //moves conveyor
    void InitDefaultCommand();
};
