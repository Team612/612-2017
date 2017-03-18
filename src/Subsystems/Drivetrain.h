#pragma once

#include "Commands/Subsystem.h"
#include "WPILib.h"
#include "CANTalon.h"
#include "lib612/DriveProfile.h"
#include "lib612/AnalogUltrasonic.h"
#include "../Ports.h"

class Drivetrain: public Subsystem {
    double DeadbandHandler(double val);
    double Limit(double val);

    double m_quick_stop_accum;
    //std::shared_ptr<Ultrasonic> ur;
    std::shared_ptr<lib612::AnalogUltrasonic> ur2;

    const double ALPHA = 0.1;
    const double DEADBAND = 0.01;
    const double TURN_SENSITIVITY = 0.7;
    const double PI = 3.141592653;
    const double RAMP_RATE = 0; // TODO This is disabled
    const uint32_t MAX_AMPS = 30;
public:
    enum DRIVE_MODE {SIMPLE, COMPLICATED};

    DRIVE_MODE drivemode;

    std::shared_ptr<CANTalon> drive_fl;
    std::shared_ptr<CANTalon> drive_ml;
    std::shared_ptr<CANTalon> drive_rl;
    std::shared_ptr<CANTalon> drive_fr;
    std::shared_ptr<CANTalon> drive_mr;
    std::shared_ptr<CANTalon> drive_rr;
    std::shared_ptr<RobotDrive> drive;
    lib612::DriveProfile* profile;
    //Drivetrain();
    Drivetrain(lib612::DriveProfile* dp);
    //void Init();
    void SetDriveProfile(lib612::DriveProfile& dp);
    void SetDriveProfile(lib612::DriveProfile* dp);
    void SetVelocity(double l, double r); //sets velocity of both sides in meters per second (tangentially)
    void SetRPM(double l, double r);      //sets rpm of both sides
    void ThrottleByRPM(double lpercent, double rpercent);
    void TankDrive(double l, double r);
    void HaloDrive(double wheel, double throttle, bool isQuickTurn);
    double GetLeftVelocity();
    double GetRightVelocity();
    void InitDefaultCommand() override;
    lib612::DriveProfile* GetCurrentProfile();
    std::shared_ptr<Ultrasonic> GetURCenter();
    std::shared_ptr<lib612::AnalogUltrasonic> GetURSide();

    void setDriveMode(DRIVE_MODE mode);
    DRIVE_MODE getDriveMode();
};
