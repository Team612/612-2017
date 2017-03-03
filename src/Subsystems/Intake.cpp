#include "Intake.h"
#include "../Robot.h"

Intake::Intake() : Subsystem("Intake") {
    /*RobotMap::intake_talon_right->SetTalonControlMode(CANTalon::TalonControlMode::kSpeedMode);
    RobotMap::intake_talon_right->SetInverted(true);
    RobotMap::intake_talon_right->SetFeedbackDevice(CANTalon::FeedbackDevice::CtreMagEncoder_Relative);
    RobotMap::intake_talon_right->SetPID(frc::SmartDashboard::GetNumber("Intake P", 0.12),
                                         frc::SmartDashboard::GetNumber("Intake I", 0.001),
                                         frc::SmartDashboard::GetNumber("Intake D", 5),
                                         frc::SmartDashboard::GetNumber("Intake ff", 0.08));
    RobotMap::intake_talon_right->SetSensorDirection(false);*/
    RobotMap::intake_talon_right->ConfigNominalOutputVoltage(+0.0f, -0.0f);
    RobotMap::intake_talon_right->ConfigPeakOutputVoltage(+12.0f, -12.0f);
    RobotMap::intake_talon_right->SetInverted(false);
    RobotMap::intake_talon_right->SetTalonControlMode(CANTalon::TalonControlMode::kThrottleMode);
    RobotMap::intake_talon_left->SetTalonControlMode(CANTalon::TalonControlMode::kFollowerMode);
    RobotMap::intake_talon_left->Set(RobotMap::intake_talon_right->GetDeviceID());
}

void Intake::InitDefaultCommand() {
    SetDefaultCommand(Robot::intakeCommand.get());
}

//TODO extend with functionality as needed
void Intake::IntakeFuel() {
    RobotMap::intake_talon_right->Set(-1);
}

void Intake::ClearBalls() {
    RobotMap::intake_talon_right->Set(1);
}

void Intake::Stop() {
    RobotMap::intake_talon_right->SetSetpoint(0);
}
