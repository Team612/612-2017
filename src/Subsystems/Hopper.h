#pragma once

#incldude "WPILib.h"
#include "Commands/Subsystem.h"

class Hopper: public frc::Subsystem {
public:
     Hopper();
     void InitDefaultCommand() override;
     void ShiftUp();
     void ShiftDown();
     void ShiftOff();


private:

};
