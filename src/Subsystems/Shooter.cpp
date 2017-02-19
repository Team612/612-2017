#include "Shooter.h"
#include "../RobotMap.h"
#include "../Commands/Shooter/Shoot.h"

Shooter::Shooter() : Subsystem("Shooter") {
    //talon = RobotMap::talon_shoot;
    RobotMap::shoot_l->SetPID(0.22, 0, 0, 0.1097);
    //get values from connected cimcoder
    RobotMap::shoot_l->SetFeedbackDevice(CANTalon::FeedbackDevice::QuadEncoder);
    //allows SetSetpoint to apply to speed from cimcoder and not from
    RobotMap::shoot_l->SetControlMode(frc::CANSpeedController::ControlMode::kSpeed);
    RobotMap::shoot_l->SetSensorDirection(false);
    RobotMap::shoot_l->ConfigNominalOutputVoltage(+0.0f, -0.0f);
    RobotMap::shoot_l->SelectProfileSlot(0);
    RobotMap::shoot_r->SetControlMode(frc::CANSpeedController::ControlMode::kFollower);
}

void Shooter::InitDefaultCommand() {
    SetDefaultCommand(new Shoot());
}

void Shooter::Spin(float speed) {
    RobotMap::shoot_l->Set(speed);
    RobotMap::shoot_r->Set(PORTS::CAN::shoot_l);
}
