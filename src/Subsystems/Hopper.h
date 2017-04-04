#pragma once

#include  "WPILib.h"
#include "Commands/Subsystem.h"

enum class FLAP_STATE { UP, DOWN };

class Hopper: public frc::Subsystem {
    FLAP_STATE state { FLAP_STATE::DOWN };
public:
     Hopper();
     void InitDefaultCommand() override;
     void ShiftUp();
     void ShiftDown();
     FLAP_STATE GetFlapState();
};
