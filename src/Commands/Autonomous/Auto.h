
#pragma once

#include "WPILib.h"
#include "Commands/Subsystem.h"
#include "string.h"

class Auto: public frc::Subsystem {
public:
     Auto();
     void InitDefaultCommand(String NameOfCommand) override;

private:

};
