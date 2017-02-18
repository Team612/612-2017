#include "Intake.h"

Intake::Intake() : Subsystem("Intake") {
    RobotMap::intake_talon_right->SetControlMode(frc::CANSpeedController::ControlMode::kSpeed);
    RobotMap::intake_talon_right->SetInverted(true);
    RobotMap::intake_talon_right->SetFeedbackDevice(CANTalon::FeedbackDevice::CtreMagEncoder_Relative);
    RobotMap::intake_talon_right->SetPID(frc::SmartDashboard::GetNumber("Intake P", 0.12),
                                         frc::SmartDashboard::GetNumber("Intake I", 0.001),
                                         frc::SmartDashboard::GetNumber("Intake D", 5),
                                         frc::SmartDashboard::GetNumber("Intake ff", 0.08));
    RobotMap::intake_talon_right->SetSensorDirection(false);
    RobotMap::intake_talon_right->ConfigNominalOutputVoltage(+0.0f, -0.0f);
    RobotMap::intake_talon_right->ConfigPeakOutputVoltage(+12.0f, -12.0f);

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
