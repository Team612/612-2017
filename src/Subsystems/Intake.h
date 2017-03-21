#pragma once

#include "../RobotMap.h"
#include "Commands/Subsystem.h"

class Intake: public frc::Subsystem {
public:
    Intake();
    void InitDefaultCommand() override;
    void IntakeFuel(); //intake with motor speed
    void ClearBalls();
    void Stop();
private:
    const double INTAKE_SPEED = 1000;
    const double RAMP_RATE = 16                                                                                                               ;
};
