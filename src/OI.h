#pragma once

#include "WPILib.h"

class OI {
private:
	std::shared_ptr<frc::XboxController> gunner;
	std::shared_ptr<frc::XboxController> driver;

public:
	OI();

	std::shared_ptr<XboxController> getdriver();
	std::shared_ptr<XboxController> getgunner();
};
