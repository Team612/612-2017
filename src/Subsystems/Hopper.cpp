#include "Hopper.h"
#include "../RobotMap.h"
Hopper::Hopper() :
    frc::Subsystem("Hopper") {
    RobotMap::hopper->Set(DoubleSolenoid::Value::kReverse);
    frc::Wait(0.5);
    RobotMap::hopper->Set(DoubleSolenoid::Value::kOff);
}

void Hopper::InitDefaultCommand() {

}
void Hopper::ShiftUp(){
    state = FLAP_STATE::UP;
    RobotMap::hopper->Set(DoubleSolenoid::Value::kForward);
    frc::Wait(0.5);
    RobotMap::hopper->Set(DoubleSolenoid::Value::kOff);
}

void Hopper::ShiftDown(){
    state = FLAP_STATE::DOWN;
    RobotMap::hopper->Set(DoubleSolenoid::Value::kReverse);
    frc::Wait(0.5);
    RobotMap::hopper->Set(DoubleSolenoid::Value::kOff);
}

FLAP_STATE Hopper::GetFlapState() { return state; }
