#pragma once

#include "Commands/Subsystem.h"
#include "WPILib.h"
#include "CANTalon.h"
#include "lib612/DriveProfile.h"
#include "../Ports.h"

class Drivetrain: public Subsystem {
public:
    std::shared_ptr<CANTalon> drive_fl;
    std::shared_ptr<CANTalon> drive_ml;
    std::shared_ptr<CANTalon> drive_rl;
    std::shared_ptr<CANTalon> drive_fr;
    std::shared_ptr<CANTalon> drive_mr;
    std::shared_ptr<CANTalon> drive_rr;
    lib612::DriveProfile* profile;
    //Drivetrain();
    Drivetrain(lib612::DriveProfile* dp);
    //void Init();
    void SetDriveProfile(lib612::DriveProfile& dp);
    void SetDriveProfile(lib612::DriveProfile* dp);
    void SetVelocity(double l, double r); //sets velocity of both sides in meters per second (tangentially)
    void SetRPM(double l, double r);      //sets rpm of both sides
    double GetLeftVelocity();
    double GetRightVelocity();
    void InitDefaultCommand() override;
    lib612::DriveProfile* GetCurrentProfile();
private:
    double pi = 3.141592653;
};
