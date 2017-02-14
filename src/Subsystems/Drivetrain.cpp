#include "Drivetrain.h"
#include <cmath>
#include "../RobotMap.h"
#include "../Commands/Drive/Drive.h"
#include "lib612/Networking/Networking.h"

Drivetrain::Drivetrain() : Subsystem("Drivetrain") {
    Init();
}



Drivetrain::Drivetrain(lib612::DriveProfile* dp) : Subsystem("Drivetrain") {
    profile = dp;
    Debug = false;
    drive_fl->SetPID(profile->P, profile->I, profile->D, profile->F);
    drive_rl->SetPID(profile->P, profile->I, profile->D, profile->F);
    drive_fr->SetPID(profile->P, profile->I, profile->D, profile->F);
    drive_rr->SetPID(profile->P, profile->I, profile->D, profile->F);
    Init();
}

Drivetrain::Drivetrain(lib612::DriveProfile* dp, bool d) : Subsystem("Drivetrain") {
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
    //SetDistancePerPulse()
    double DistancePerWheelRotation = pi*profile->WheelDiameter;
    double WheelRPMPerPulsePer100ms = profile->NativeToRPM * profile->EncoderToWheel;
    double WheelRotationsPerPulse = WheelRPMPerPulsePer100ms * (60/0.1);
    double DistancePerPulse = DistancePerWheelRotation * WheelRotationsPerPulse;
    RobotMap::drivetrainleft_encoder->SetDistancePerPulse(DistancePerPulse);
    RobotMap::drivetrainright_encoder->SetDistancePerPulse(DistancePerPulse);

    //update Smart Dashboard
    lib612::Networking::AddFunction([this](){
        frc::SmartDashboard::PutNumber("Drivetrain P",this->profile->P );
        frc::SmartDashboard::PutNumber("Drivetrain I",this->profile->I );
        frc::SmartDashboard::PutNumber("Drivetrain D", this->profile->D );
        frc::SmartDashboard::PutNumber("Drivetrain F", this->profile->F );

    });
}

void Drivetrain::SetVelocity(double l, double r) {
    double pi = 3.141592653;
    double TargetLeft = (60*(l/profile->WheelFriction))/(profile->WheelDiameter*pi); //Converts l to left wheel rpm
    if(std::abs(TargetLeft) > profile->WheelMaxRPM) {
        TargetLeft = (std::abs(TargetLeft)/TargetLeft)*profile->WheelMaxRPM; //If TargetLeft is greater that WheelMaxRPM, Set TargetLeft to WheelMaxRPM with correct sign
    }
    double TargetRight = (60*(r/profile->WheelFriction))/(profile->WheelDiameter*pi); //Converts r to right wheel rpm
    if(std::abs(TargetRight) > profile->WheelMaxRPM) {
        TargetLeft = (std::abs(TargetRight)/TargetRight)*profile->WheelMaxRPM; //If TargetRight is greater that WheelMaxRPM, Set TargetRight to WheelMaxRPM with correct sign
    }
    TargetLeft = (TargetLeft/profile->EncoderToWheel/profile->NativeToRPM);   //Convert to native encoder units (also using EncoderToWheel for gearbox)
    TargetRight = (TargetRight/profile->EncoderToWheel/profile->NativeToRPM); //Convert to native encoder units (also using EncoderToWheel for gearbox)
    if(profile->TwoEncoder) {
        if(profile->LeftTalonEncoder == 0) {
            drive_fl->SetSetpoint(TargetLeft);
            drive_rl->Set(drive_fl->GetDeviceID());
        }
        else {
            drive_rl->SetSetpoint(TargetLeft);
            drive_fl->Set(drive_rl->GetDeviceID());
        }
        if(profile->RightTalonEncoder == 0) {
            drive_fr->SetSetpoint(TargetRight);
            drive_rr->Set(drive_fr->GetDeviceID());
        }
        else {
            drive_rr->SetSetpoint(TargetRight);
            drive_fr->Set(drive_rr->GetDeviceID());
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
