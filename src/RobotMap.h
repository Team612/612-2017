#pragma once

#include "WPILib.h"
#include "CANTalon.h"

class RobotMap {
public:

    static std::shared_ptr<CANTalon> shooter_l;
    static std::shared_ptr<CANTalon> shooter_r;
    static std::shared_ptr<CANTalon> drive_fl;
    static std::shared_ptr<CANTalon> drive_ml;
    static std::shared_ptr<CANTalon> drive_rl;
    static std::shared_ptr<CANTalon> drive_fr;
    static std::shared_ptr<CANTalon> drive_mr;
    static std::shared_ptr<CANTalon> drive_rr;
    static std::shared_ptr<CANTalon> climber_l;
    static std::shared_ptr<CANTalon> climber_r;
    static std::shared_ptr<RobotDrive> drive;

    static std::shared_ptr<CANTalon> intake_talon_left;
    static std::shared_ptr<CANTalon> intake_talon_right;
    static std::shared_ptr<Servo> grabber;

    static std::shared_ptr<PowerDistributionPanel> pdp;
    //static std::shared_ptr<RobotDrive> drive;

    static void init();
};
