#pragma once

#include "Commands/Subsystem.h"
#include "WPILib.h"
#include "CANTalon.h"

class Shooter: public Subsystem {
private:
    //std::shared_ptr<CANTalon> talon;

public:
    Shooter();
    void InitDefaultCommand();
};
