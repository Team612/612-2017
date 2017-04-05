#pragma once

#include "Commands/Subsystem.h"
#include "../RobotMap.h"


class Shifter: public frc::Subsystem {
public:
     Shifter();
     void InitDefaultCommand() override;
     void ShiftUp();
     void ShiftDown();
     void ShiftOff();

private:

};
