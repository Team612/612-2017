#pragma once

#include "Commands/Subsystem.h"
#include "WPILib.h"
#include "CANTalon.h"
#include "DriveProfile.h"
#include "../Ports.h"

class Drivetrain: public Subsystem {
private:
    std::shared_ptr<CANTalon> drive_fl;
    std::shared_ptr<CANTalon> drive_rl;
    std::shared_ptr<CANTalon> drive_fr;
    std::shared_ptr<CANTalon> drive_rr;
    DriveProfile* profile;
    bool Debug; //if true, debuging is on
public:
    Drivetrain();
    Drivetrain(DriveProfile* dp);
    Drivetrain(DriveProfile* dp, bool d);
    void Init();
    void SetDriveProfile(DriveProfile dp);
    void SetVelocity(double l, double r); //in meters per second (tangentially)
    double GetLeftVelocity();
    double GetRightVelocity();
    void InitDefaultCommand();
};
