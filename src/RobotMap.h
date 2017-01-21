#pragma once

#include "WPILib.h"

class RobotMap {
public:
	static std::shared_ptr<SpeedController> talon_shoot;
	static std::shared_ptr<SpeedController> drive_fl;
	static std::shared_ptr<SpeedController> drive_rl;
	static std::shared_ptr<SpeedController> drive_fr;
	static std::shared_ptr<SpeedController> drive_rr;
	static std::shared_ptr<RobotDrive> drive;
	static std::shared_ptr<Encoder> drivetrainleft_encoder;
	static std::shared_ptr<Encoder> drivetrainright_encoder;


	static void init();
};
