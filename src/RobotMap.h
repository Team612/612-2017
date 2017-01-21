#pragma once

#include "WPILib.h"
#include "CANTalon.h"

class RobotMap {
public:
    static std::shared_ptr<CANTalon> talon_shoot;
    static std::shared_ptr<CANTalon> drive_fl;
    static std::shared_ptr<CANTalon> drive_rl;
    static std::shared_ptr<CANTalon> drive_fr;
    static std::shared_ptr<CANTalon> drive_rr;
    static std::shared_ptr<RobotDrive> drive;
    static std::shared_ptr<Encoder> drivetrainleft_encoder;
    static std::shared_ptr<Encoder> drivetrainright_encoder;


    static void init();
};
