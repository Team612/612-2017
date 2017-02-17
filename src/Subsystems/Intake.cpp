#include "Intake.h"

Intake::Intake() : Subsystem("Intake") {
    RobotMap::intake_talon_right->SetControlMode(frc::CANSpeedController::ControlMode::kSpeed);
    RobotMap::intake_talon_right->SetInverted(true);
    RobotMap::intake_talon_left->SetFeedbackDevice(CANTalon::FeedbackDevice::CtreMagEncoder_Relative);
    RobotMap::intake_talon_left->SetControlMode(frc::CANSpeedController::ControlMode::kFollower);
    RobotMap::intake_talon_left->Set(RobotMap::intake_talon_right->GetDeviceID());
}

void Intake::InitDefaultCommand() {

}

void Intake::IntakeFuel() {
    RobotMap::intake_talon_right->SetSetpoint(INTAKE_SPEED);
}

void Intake::ClearBalls() {
    RobotMap::intake_talon_right->SetSetpoint(-INTAKE_SPEED / 3);
}

void Intake::Stop() {
    RobotMap::intake_talon_right->SetSetpoint(0);
}
