#pragma once

#include "Commands/Subsystem.h"
#include "WPILib.h"

class Drivetrain: public Subsystem {
private:
    std::shared_ptr<Encoder> left_encoder;
    std::shared_ptr<Encoder> right_encoder;
public:
    Drivetrain();
    void InitDefaultCommand();
};
