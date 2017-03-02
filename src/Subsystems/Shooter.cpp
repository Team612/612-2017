#include "Shooter.h"
#include "../RobotMap.h"
#include "../Commands/Shooter/Shoot.h"

Shooter::Shooter() : Subsystem("Shooter") {
    //talon = RobotMap::talon_shoot;
    RobotMap::shooter_l->SetPID(0.22, 0, 0, 0.1097);
    //get values from connected cimcoder
    RobotMap::shooter_l->SetFeedbackDevice(CANTalon::FeedbackDevice::QuadEncoder);
    //allows SetSetpoint to apply to speed from cimcoder and not from
    RobotMap::shooter_l->SetTalonControlMode(CANTalon::TalonControlMode::kSpeedMode);
    RobotMap::shooter_l->SetSensorDirection(false);
    RobotMap::shooter_l->ConfigNominalOutputVoltage(+0.0f, -0.0f);
    RobotMap::shooter_l->SelectProfileSlot(0);
    RobotMap::shooter_r->SetTalonControlMode(CANTalon::TalonControlMode::kFollowerMode);
    RobotMap::shooter_r->Set(PORTS::CAN::shooter_talon_right);
}

void Shooter::InitDefaultCommand() {
    SetDefaultCommand(new Shoot());
}

void Shooter::Spin(float speed) {
    RobotMap::shooter_l->Set(speed);
    //RobotMap::shooter_r->Set(PORTS::CAN::shooter_talon_left);
}

void Shooter::Agitate() {
    RobotMap::agitator->Set(0.2f);
}
