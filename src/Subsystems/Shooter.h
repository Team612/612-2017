#pragma once

#include "Commands/Subsystem.h"
#include "WPILib.h"

class Shooter: public Subsystem {
private:
	std::shared_ptr<SpeedController> talon;

public:
	Shooter();
	void InitDefaultCommand();
};
