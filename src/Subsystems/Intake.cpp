#include "Intake.h"
#include "../Robot.h"
#include "lib612/Networking/Networking.h"

Intake::Intake() : Subsystem("Intake") {
    /*RobotMap::intake_talon_right->SetTalonControlMode(CANTalon::TalonControlMode::kSpeedMode);
    RobotMap::intake_talon_right->SetInverted(true);
    RobotMap::intake_talon_right->SetFeedbackDevice(CANTalon::FeedbackDevice::CtreMagEncoder_Relative);
    RobotMap::intake_talon_right->SetPID(frc::SmartDashboard::GetNumber("Intake P", 0.12),
                                         frc::SmartDashboard::GetNumber("Intake I", 0.001),
                                         frc::SmartDashboard::GetNumber("Intake D", 5),
                                         frc::SmartDashboard::GetNumber("Intake ff", 0.08));
    RobotMap::intake_talon_right->SetSensorDirection(false);*/
    RobotMap::intake_talon_right->SetTalonControlMode(CANTalon::TalonControlMode::kThrottleMode);
    RobotMap::intake_talon_right->SetVoltageRampRate(RAMP_RATE);
    RobotMap::intake_talon_left->SetTalonControlMode(CANTalon::TalonControlMode::kThrottleMode);
    RobotMap::intake_talon_left->SetVoltageRampRate(RAMP_RATE);
//    RobotMap::intake_talon_left->SetTalonControlMode(CANTalon::TalonControlMode::kFollowerMode);
//    RobotMap::intake_talon_left->SetClosedLoopOutputDirection(true);
    lib612::Networking::AddFunction([](){
        frc::SmartDashboard::PutNumber("Total Intake current", RobotMap::intake_talon_left->GetOutputCurrent() +
                                                               RobotMap::intake_talon_right->GetOutputCurrent());
    });
}

void Intake::InitDefaultCommand() {
    SetDefaultCommand(Robot::intakeCommand.get());
}

//TODO extend with functionality as needed
void Intake::IntakeFuel() {
    RobotMap::intake_talon_right->Set(-1);
    RobotMap::intake_talon_left->Set(1);
}

void Intake::ClearBalls() {
    RobotMap::intake_talon_right->Set(1);
    RobotMap::intake_talon_left->Set(-1);
}

void Intake::Stop() {
    RobotMap::intake_talon_right->Set(0);
    RobotMap::intake_talon_left->Set(0);
}
