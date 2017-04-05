#pragma once

#include "Commands/Subsystem.h"
#include "DoubleSolenoid.h"

enum class GearState { OPEN = 0, CLOSED = 1 };

class GearSystem: public Subsystem {
    std::shared_ptr<frc::DoubleSolenoid> actuator { };
    GearState state { GearState::CLOSED };
public:
    GearSystem();

    void InitDefaultCommand() override;

    void GearOpen();
    void GearClose();
    GearState GetGearState();
};
