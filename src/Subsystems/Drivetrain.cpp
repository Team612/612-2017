#include "Drivetrain.h"
#include <cmath>
#include "../RobotMap.h"
#include "../Commands/Drive/Drive.h"
#include "lib612/Networking/Networking.h"

Drivetrain::Drivetrain(lib612::DriveProfile* dp) : Subsystem("Drivetrain") {
    profile = dp;
    drive_ml->SetPID(profile->P, profile->I, profile->D, profile->F);
    drive_mr->SetPID(profile->P, profile->I, profile->D, profile->F);
    drive_ml->SetFeedbackDevice(CANTalon::FeedbackDevice::QuadEncoder);
    drive_mr->SetFeedbackDevice(CANTalon::FeedbackDevice::QuadEncoder);
    drive_ml->SetTalonControlMode(CANTalon::TalonControlMode::kSpeedMode);
    drive_mr->SetTalonControlMode(CANTalon::TalonControlMode::kSpeedMode);
    drive_ml->SetTalonControlMode(CANTalon::TalonControlMode::kFollowerMode);
    drive_mr->SetTalonControlMode(CANTalon::TalonControlMode::kFollowerMode);
    drive_ml->SetTalonControlMode(CANTalon::TalonControlMode::kFollowerMode);
    drive_mr->SetTalonControlMode(CANTalon::TalonControlMode::kFollowerMode);

    //SetDistancePerPulse()
    //TODO: Are these being used?
    //double DistancePerWheelRotation = pi*profile->WheelDiameter;
    //double WheelRPMPerPulsePer100ms = profile->NativeToRPM * profile->EncoderToWheel;
    //double WheelRotationsPerPulse = WheelRPMPerPulsePer100ms * (60/0.1);
    //double DistancePerPulse = DistancePerWheelRotation * WheelRotationsPerPulse;

    //update Smart Dashboard
    lib612::Networking::AddFunction([this](){
        frc::SmartDashboard::PutNumber("Drivetrain P",this->profile->P );
        frc::SmartDashboard::PutNumber("Drivetrain I",this->profile->I );
        frc::SmartDashboard::PutNumber("Drivetrain D", this->profile->D );
        frc::SmartDashboard::PutNumber("Drivetrain F", this->profile->F );
    });
}

void Drivetrain::SetDriveProfile(lib612::DriveProfile& dp) {
    *profile = dp;
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

    drive_ml->SetSetpoint(TargetLeft);
    drive_fl->Set(drive_ml->GetDeviceID());
    drive_rl->Set(drive_ml->GetDeviceID());
    drive_mr->SetSetpoint(TargetRight);
    drive_fr->Set(drive_mr->GetDeviceID());
    drive_rr->Set(drive_mr->GetDeviceID());
}

void Drivetrain::SetThrottle(double l, double r) {
    double left, right;
    if(abs(l) > 1) {
        if (l < 0)
            left = -1;
        else
            left = 1;
    }

    if(abs(r) > 1) {
        if (r < 0)
            right = -1;
        else
            right = 1;
    }
    SetRPM(left * profile->WheelMaxRPM, right * profile->WheelMaxRPM); //Set the RPM to a percentage of the maximum RPM
}

lib612::DriveProfile* Drivetrain::GetCurrentProfile() {
    return profile;
}

void Drivetrain::InitDefaultCommand() {
    printf("Default command for Drivetrain\n");
    SetDefaultCommand(new Drive());
}
