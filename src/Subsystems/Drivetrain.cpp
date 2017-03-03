#include "Drivetrain.h"
#include "../Commands/Drive/Drive.h"
#include "lib612/Networking/Networking.h"
#include "../RobotMap.h"
#include "../Robot.h"

Drivetrain::Drivetrain(lib612::DriveProfile* dp) : Subsystem("Drivetrain") {
    ur = RobotMap::ultrasonic;
    ur2 = RobotMap::new_ultrasonic;
    profile = dp;

    //Make sure we're using the actual talon objects and not making our out copies
    this->drive_mr.reset(RobotMap::drive_mr.get());
    this->drive_fr.reset(RobotMap::drive_fr.get());
    this->drive_rr.reset(RobotMap::drive_rr.get());
    this->drive_ml.reset(RobotMap::drive_ml.get());
    this->drive_fl.reset(RobotMap::drive_fl.get());
    this->drive_rl.reset(RobotMap::drive_rl.get());

    //check if null
    if(this->drive_mr == nullptr || this->drive_fr == nullptr || this->drive_rr == nullptr || this->drive_ml == nullptr || this->drive_fl == nullptr || this->drive_rl == nullptr)
        std::cout << "Yolo one of these are nullo lolololo" << std::endl;

    /*this->drive_ml->SetPID(profile->P, profile->I, profile->D, profile->F);
    this->drive_mr->SetPID(profile->P, profile->I, profile->D, profile->F);
    this->drive_ml->SetFeedbackDevice(CANTalon::FeedbackDevice::QuadEncoder);
    this->drive_mr->SetFeedbackDevice(CANTalon::FeedbackDevice::QuadEncoder);*/

    this->drive_ml->SetTalonControlMode(CANTalon::TalonControlMode::kThrottleMode);
    this->drive_mr->SetTalonControlMode(CANTalon::TalonControlMode::kThrottleMode);
    this->drive_fl->SetTalonControlMode(CANTalon::TalonControlMode::kFollowerMode);
    this->drive_fl->Set(PORTS::CAN::drive_talonML);
    this->drive_fr->SetTalonControlMode(CANTalon::TalonControlMode::kFollowerMode);
    this->drive_fr->Set(PORTS::CAN::drive_talonMR);
    //this->drive_fr->SetClosedLoopOutputDirection(true);
    this->drive_rl->SetTalonControlMode(CANTalon::TalonControlMode::kFollowerMode);
    this->drive_rl->Set(PORTS::CAN::drive_talonML);
    this->drive_rr->SetTalonControlMode(CANTalon::TalonControlMode::kFollowerMode);
    this->drive_rr->Set(PORTS::CAN::drive_talonMR);
    this->drive_ml->SetVoltageRampRate(RAMP_RATE);
    this->drive_mr->SetVoltageRampRate(RAMP_RATE);
    this->drive_ml->SetInverted(true);
    this->drive_mr->SetInverted(false);

    this->drive.reset(RobotMap::drive.get());

    //TODO: Are these being used?
    //SetDistancePerPulse()
    //double DistancePerWheelRotation = pi*profile->WheelDiameter;
    //double WheelRPMPerPulsePer100ms = profile->NativeToRPM * profile->EncoderToWheel;
    //double WheelRotationsPerPulse = WheelRPMPerPulsePer100ms * (60/0.1);
    //double DistancePerPulse = DistancePerWheelRotation * WheelRotationsPerPulse;

    //update Smart Dashboard
    lib612::Networking::AddFunction([this](){
        frc::SmartDashboard::PutNumber("Drivetrain P",this->profile->P);
        frc::SmartDashboard::PutNumber("Drivetrain I",this->profile->I);
        frc::SmartDashboard::PutNumber("Drivetrain D", this->profile->D);
        frc::SmartDashboard::PutNumber("Drivetrain F", this->profile->F);
        frc::SmartDashboard::PutNumber("Total Robot Current (Sum of all Channels)", RobotMap::pdp->GetTotalCurrent());
        frc::SmartDashboard::PutNumber("Climber Current", RobotMap::pdp->GetCurrent(15));
        frc::SmartDashboard::PutNumber("Ultrasonic Distance (mm)", ur->GetRangeMM());
        frc::SmartDashboard::PutNumber("New Ultrasonic Distance (inches) by regression combination", ur2->GetDistanceInches());
    });
}

void Drivetrain::SetDriveProfile(lib612::DriveProfile& dp) {
    *profile = dp;
}

void Drivetrain::SetDriveProfile(lib612::DriveProfile* dp) {
    profile = dp;
}

void Drivetrain::SetVelocity(double l, double r) {
    double TargetLeft = (60*(l/profile->WheelFriction))/(profile->WheelDiameter*PI); //Converts l to left wheel rpm
    double TargetRight = (60*(r/profile->WheelFriction))/(profile->WheelDiameter*PI); //Converts r to right wheel rpm
    SetRPM(TargetLeft, TargetRight);
}

void Drivetrain::SetRPM(double l, double r) {
    double TargetLeft = l;
    double TargetRight = r;
    if(std::abs(TargetLeft) > profile->WheelMaxRPM) {
        TargetLeft = (std::abs(TargetLeft)/TargetLeft)*profile->WheelMaxRPM; //If TargetLeft is greater that WheelMaxRPM, Set TargetLeft to WheelMaxRPM with correct sign
    }
    if(std::abs(TargetRight) > profile->WheelMaxRPM) {
        TargetLeft = (std::abs(TargetRight)/TargetRight)*profile->WheelMaxRPM; //If TargetRight is greater that WheelMaxRPM, Set TargetRight to WheelMaxRPM with correct sign
    }

    drive_ml->SetSetpoint(TargetLeft/profile->NativeToRPM);
    drive_fl->Set(drive_ml->GetDeviceID());
    drive_rl->Set(drive_ml->GetDeviceID());
    drive_mr->SetSetpoint(TargetRight/profile->NativeToRPM);
    drive_fr->Set(drive_mr->GetDeviceID());
    drive_rr->Set(drive_mr->GetDeviceID());
}

lib612::DriveProfile* Drivetrain::GetCurrentProfile() {
    return profile;
}

double Drivetrain::GetLeftVelocity() {
    return drive_ml->GetSetpoint();
}

double Drivetrain::GetRightVelocity() {
    return drive_mr->GetSetpoint();
}

void Drivetrain::ThrottleByRPM(double lpercent, double rpercent) {
    SetRPM(Limit(lpercent) * profile->WheelMaxRPM, Limit(rpercent) * profile->WheelMaxRPM);
}

std::shared_ptr<Ultrasonic> Drivetrain::GetURCenter() {
    return ur; //guess
}

std::shared_ptr<lib612::AnalogUltrasonic> Drivetrain::GetURSide() {
    return ur2;
}
void Drivetrain::InitDefaultCommand() {
    printf("Default command for Drivetrain\n");
    SetDefaultCommand(new Drive());
}

void Drivetrain::TankDrive(double raw_left, double raw_right){
    double l = DeadbandHandler(raw_left);
    double r = DeadbandHandler(raw_right);
    std::cout << "Drivetrain.cpp l: " << l << " r: " << r << std::endl;
    if (l == 0) {
        drive_ml->SetVoltageRampRate(0);
        drive_ml->Set(0);
        drive_ml->SetVoltageRampRate(RAMP_RATE);
    } else {
        drive_ml->Set(Limit(l));
    }
    if(r == 0) {
        drive_mr->SetVoltageRampRate(0);
        drive_mr->Set(0);
        drive_mr->SetVoltageRampRate(RAMP_RATE);
    } else {
        drive_mr->Set(Limit(r));
    }
}

void Drivetrain::HaloDrive(double wheel, double throttle, bool isQuickTurn) {
    double over_power, angular_power;
    if (isQuickTurn) {
        if (std::abs(throttle) < 0.2) {
            m_quick_stop_accum = (1 - ALPHA) * m_quick_stop_accum + ALPHA * Limit(wheel) * 2;
        }
        over_power = 1.0;
        angular_power = wheel;
    } else {
        over_power = 0.0;
        angular_power = std::abs(throttle) * wheel * TURN_SENSITIVITY - m_quick_stop_accum;
        if (m_quick_stop_accum > 1) {
            m_quick_stop_accum -= 1;
        } else if (m_quick_stop_accum < -1) {
            m_quick_stop_accum += 1;
        } else {
            m_quick_stop_accum = 0.0;
        }
    }

    double right = throttle - angular_power;
    double left = throttle + angular_power;

    if (left > 1.0) {
        right -= over_power * (left - 1.0);
        left = 1.0;
    } else if (right > 1.0) {
        left -= over_power * (right - 1.0);
        right = 1.0;
    } else if (left < -1.0) {
        right += over_power * (-1.0 - left);
        left = -1.0;
    } else if (right < -1.0) {
        left += over_power * (-1.0 - right);
        right = -1.0;
    }
    //std::cout << "Drivetrain.cpp: Left: " << left << " Right: " << right << std::endl;
    TankDrive(left, right);
}

Drivetrain::DRIVE_MODE Drivetrain::getDriveMode() {
    return drivemode;
}

void Drivetrain::setDriveMode(Drivetrain::DRIVE_MODE mode){
    drivemode = mode;
}

double Drivetrain::DeadbandHandler(double val) {
    return (std::abs(val) > DEADBAND) ? val : 0.0;
}

double Drivetrain::Limit(double val) {
    return (std::abs(val) > 1) ? (val > 0 ? 1 : -1) : val;
}
