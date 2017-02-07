#pragma once

#include "WPILib.h"
#include "../RobotMap.h"
#include "Commands/Subsystem.h"

class Intake: public frc::Subsystem {
public:
       Intake();
       void InitDefaultCommand() override;
       void IntakeFuel(float speed); //intake with motor speed

private:

};
