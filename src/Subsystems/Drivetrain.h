#pragma once

#include "Commands/Subsystem.h"
#include "WPILib.h"
#include "CANTalon.h"
#include "lib612/DriveProfile.h"
#include "../Ports.h"

class Drivetrain: public Subsystem {
public:
    enum DRIVE_MODE {SIMPLE, COMPLICATED};

    DRIVE_MODE drivemode;

    std::shared_ptr<CANTalon> drive_fl;
    std::shared_ptr<CANTalon> drive_ml;
    std::shared_ptr<CANTalon> drive_rl;
    std::shared_ptr<CANTalon> drive_fr;
    std::shared_ptr<CANTalon> drive_mr;
    std::shared_ptr<CANTalon> drive_rr;
    std::shared_ptr<Ultrasonic> ur;
    std::shared_ptr<RobotDrive> drive;
    lib612::DriveProfile* profile;
    //Drivetrain();
    Drivetrain(lib612::DriveProfile* dp);
    //void Init();
    void SetDriveProfile(lib612::DriveProfile& dp);
    void SetDriveProfile(lib612::DriveProfile* dp);
    void SetVelocity(double l, double r); //sets velocity of both sides in meters per second (tangentially)
    void SetRPM(double l, double r);      //sets rpm of both sides
    void Throttle(double lpercent, double rpercent);
    void TeleOpDrive(double l, double r);
    double GetLeftVelocity();
    double GetRightVelocity();
    void InitDefaultCommand() override;
    lib612::DriveProfile* GetCurrentProfile();
    std::shared_ptr<Ultrasonic> GetURCenter();

    void setDriveMode(DRIVE_MODE mode);
    DRIVE_MODE getDriveMode();

    double RAMP_RATE = 20;
private:
    double pi = 3.141592653;
};
