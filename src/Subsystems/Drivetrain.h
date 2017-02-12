#pragma once

#include "Commands/Subsystem.h"
#include "WPILib.h"
#include "CANTalon.h"
#include "lib612/DriveProfile.h"
#include "../Ports.h"

class Drivetrain: public Subsystem {
public:
    std::shared_ptr<CANTalon> drive_fl;
    std::shared_ptr<CANTalon> drive_rl;
    std::shared_ptr<CANTalon> drive_fr;
    std::shared_ptr<CANTalon> drive_rr;
    lib612::DriveProfile* profile;
    bool Debug; //if true, debuging is on
    Drivetrain();
    Drivetrain(lib612::DriveProfile* dp);
    Drivetrain(lib612::DriveProfile* dp, bool d);
    void Init();
    void SetDriveProfile(lib612::DriveProfile dp);
    void SetVelocity(double l, double r); //in meters per second (tangentially)
    double GetLeftVelocity();
    double GetRightVelocity();
    void InitDefaultCommand();
private:
    double pi = 3.141592653;
};
