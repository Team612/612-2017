#pragma once

#include "Commands/Subsystem.h"
#include "WPILib.h"


class Climber: public Subsystem {
private:
public:
	Climber();
	void InitDefaultCommand();
};
