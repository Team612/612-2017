#pragma once

#include "WPILib.h"

class SimpleSideGear : public Command {
    double base_speed;
    bool is_inverted;
    frc::Timer time { };
public:
    SimpleSideGear(double speed, double timeout, bool inverted = false);
    void Initialize() override;
    void Execute() override;
    bool IsFinished() override;
    void End() override;
    void Interrupted() override;
};

