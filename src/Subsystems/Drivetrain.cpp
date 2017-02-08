#include "Drivetrain.h"
#include <cmath>
#include "../RobotMap.h"
#include "../Commands/Drive/Drive.h"

Drivetrain::Drivetrain() : Subsystem("Drivetrain") {
    Init();
}

Drivetrain::Drivetrain(DriveProfile* dp) : Subsystem("Drivetrain") {
    profile = dp;
    Debug = false;
    drive_fl->SetPID(profile->P, profile->I, profile->D, profile->F);
    drive_rl->SetPID(profile->P, profile->I, profile->D, profile->F);
    drive_fr->SetPID(profile->P, profile->I, profile->D, profile->F);
    drive_rr->SetPID(profile->P, profile->I, profile->D, profile->F);
    Init();
}

Drivetrain::Drivetrain(DriveProfile* dp, bool d) : Subsystem("Drivetrain") {
    profile = dp;
    Debug = d;
    drive_fl->SetPID(profile->P, profile->I, profile->D, profile->F);
    drive_rl->SetPID(profile->P, profile->I, profile->D, profile->F);
    drive_fr->SetPID(profile->P, profile->I, profile->D, profile->F);
    drive_rr->SetPID(profile->P, profile->I, profile->D, profile->F);
    Init();
}

void Drivetrain::Init() {
    if(profile->TwoEncoder) {
        if(profile->LeftTalonEncoder == 0) {
            drive_fl->SetFeedbackDevice(CANTalon::FeedbackDevice::QuadEncoder);
            drive_fl->SetTalonControlMode(CANTalon::TalonControlMode::kSpeedMode);
            drive_rl->SetTalonControlMode(CANTalon::TalonControlMode::kFollowerMode);
            drive_rl->Set(drive_fl->GetDeviceID());
        }
        else {
            drive_rl->SetFeedbackDevice(CANTalon::FeedbackDevice::QuadEncoder);
            drive_rl->SetTalonControlMode(CANTalon::TalonControlMode::kSpeedMode);
            drive_fl->SetTalonControlMode(CANTalon::TalonControlMode::kFollowerMode);
            drive_fl->Set(drive_rl->GetDeviceID());
        }
        if(profile->RightTalonEncoder == 0) {
            drive_fr->SetFeedbackDevice(CANTalon::FeedbackDevice::QuadEncoder);
            drive_fr->SetTalonControlMode(CANTalon::TalonControlMode::kSpeedMode);
            drive_rr->SetTalonControlMode(CANTalon::TalonControlMode::kFollowerMode);
            drive_rr->Set(drive_fr->GetDeviceID());
        }
        else {
            drive_rr->SetFeedbackDevice(CANTalon::FeedbackDevice::QuadEncoder);
            drive_rr->SetTalonControlMode(CANTalon::TalonControlMode::kSpeedMode);
            drive_fr->SetTalonControlMode(CANTalon::TalonControlMode::kFollowerMode);
            drive_fr->Set(drive_rr->GetDeviceID());
        }
    }
    else {
        drive_fl->SetFeedbackDevice(CANTalon::FeedbackDevice::QuadEncoder);
        drive_fl->SetTalonControlMode(CANTalon::TalonControlMode::kSpeedMode);
        drive_rl->SetFeedbackDevice(CANTalon::FeedbackDevice::QuadEncoder);
        drive_rl->SetTalonControlMode(CANTalon::TalonControlMode::kSpeedMode);
        drive_fr->SetFeedbackDevice(CANTalon::FeedbackDevice::QuadEncoder);
        drive_fr->SetTalonControlMode(CANTalon::TalonControlMode::kSpeedMode);
        drive_rr->SetFeedbackDevice(CANTalon::FeedbackDevice::QuadEncoder);
        drive_rr->SetTalonControlMode(CANTalon::TalonControlMode::kSpeedMode);
    }
}

void Drivetrain::SetVelocity(double l, double r) {
    double pi = 3.141592653;
    double TargetLeft = (60*(l/profile->WheelFriction))/(profile->WheelDiameter*pi);
    if(std::abs(TargetLeft) > profile->WheelMaxRPM) {
        TargetLeft = (std::abs(TargetLeft)/TargetLeft)*profile->WheelMaxRPM;
    }
    double TargetRight = (60*(r/profile->WheelFriction))/(profile->WheelDiameter*pi);
    if(std::abs(TargetRight) > profile->WheelMaxRPM) {
        TargetLeft = (std::abs(TargetRight)/TargetRight)*profile->WheelMaxRPM;
    }
    TargetLeft = TargetLeft/profile->NativeToRPM; //Convert to native encoder units
    TargetRight = TargetRight/profile->NativeToRPM; //Convert to native encoder units
    if(profile->TwoEncoder) {
        if(profile->LeftTalonEncoder == 0) {
            drive_fl->SetSetpoint(TargetLeft);
        }
        else {
            drive_rl->SetSetpoint(TargetLeft);
        }
        if(profile->RightTalonEncoder == 0) {
            drive_fr->SetSetpoint(TargetRight);
        }
        else {
            drive_rr->SetSetpoint(TargetRight);
        }
    }
    else {
        drive_fl->SetSetpoint(TargetLeft);
        drive_rl->SetSetpoint(TargetLeft);
        drive_fr->SetSetpoint(TargetRight);
        drive_rr->SetSetpoint(TargetRight);
    }
}

void Drivetrain::InitDefaultCommand() {
    printf("Default command for Drivetrain\n");
    SetDefaultCommand(new Drive());
}
