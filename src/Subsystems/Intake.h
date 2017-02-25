#pragma once

#include "WPILib.h"
#include "../RobotMap.h"
#include "Commands/Subsystem.h"

class Intake: public frc::Subsystem {
public:
    Intake();
    void InitDefaultCommand() override;
    void SetIntake(float input); //Directly set intake speed
    void IntakeFuel(); //intake with motor speed
    void ClearBalls();
    void Stop();
private:
    const double INTAKE_SPEED = 1000;
};
