#include "Drivetrain.h"
#include "../Commands/Drive/Drive.h"
#include "lib612/Networking/Networking.h"
#include "../RobotMap.h"

Drivetrain::Drivetrain(lib612::DriveProfile* dp) : Subsystem("Drivetrain") {
    ur = std::make_shared<Ultrasonic>(PORTS::DIO::ultrasonic_in, PORTS::DIO::ultrasonic_out, frc::Ultrasonic::DistanceUnit::kMilliMeters);
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

    this->drive_ml->SetPID(profile->P, profile->I, profile->D, profile->F);
    this->drive_mr->SetPID(profile->P, profile->I, profile->D, profile->F);
    this->drive_ml->SetFeedbackDevice(CANTalon::FeedbackDevice::QuadEncoder);
    this->drive_mr->SetFeedbackDevice(CANTalon::FeedbackDevice::QuadEncoder);
    this->drive_ml->SetTalonControlMode(CANTalon::TalonControlMode::kSpeedMode);
    this->drive_mr->SetTalonControlMode(CANTalon::TalonControlMode::kSpeedMode);
    this->drive_ml->SetTalonControlMode(CANTalon::TalonControlMode::kFollowerMode);
    this->drive_mr->SetTalonControlMode(CANTalon::TalonControlMode::kFollowerMode);
    this->drive_ml->SetTalonControlMode(CANTalon::TalonControlMode::kFollowerMode);
    this->drive_mr->SetTalonControlMode(CANTalon::TalonControlMode::kFollowerMode);

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
    });
}

void Drivetrain::SetDriveProfile(lib612::DriveProfile& dp) {
    *profile = dp;
}

void Drivetrain::SetDriveProfile(lib612::DriveProfile* dp) {
    profile = dp;
}

void Drivetrain::SetVelocity(double l, double r) {
    double TargetLeft = (60*(l/profile->WheelFriction))/(profile->WheelDiameter*pi); //Converts l to left wheel rpm
    double TargetRight = (60*(r/profile->WheelFriction))/(profile->WheelDiameter*pi); //Converts r to right wheel rpm
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

void Drivetrain::Throttle(double lpercent, double rpercent) {
    double left = lpercent, right = rpercent;
    //deal with dumb people who set motors to more than 100%
    if(left > 0)
        left = abs(left) > 1 ? 1 : left;
    else
        left = abs(left) > 1 ? -1 : left;

    if(right > 0)
        right = abs(right) > 1 ? 1 : right;
    else
        right = abs(right) > 1 ? -1 : right;

    SetRPM(left * profile->WheelMaxRPM, right * profile->WheelMaxRPM);
}

std::shared_ptr<Ultrasonic> Drivetrain::GetURCenter() {
    return ur; //guess
}
void Drivetrain::InitDefaultCommand() {
    printf("Default command for Drivetrain\n");
    SetDefaultCommand(new Drive());
}
