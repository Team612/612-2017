#include "Hopper.h"
#include "../RobotMap.h"
Hopper::Hopper() :
    frc::Subsystem("Hopper") {
    RobotMap::hopper->Set(DoubleSolenoid::Value::kReverse);
}

void Hopper::InitDefaultCommand() {

}
void Hopper::ShiftUp(){
    state = FLAP_STATE::UP;
    RobotMap::hopper->Set(DoubleSolenoid::Value::kForward);
}

void Hopper::ShiftDown(){
    state = FLAP_STATE::DOWN;
    RobotMap::hopper->Set(DoubleSolenoid::Value::kReverse);
}

FLAP_STATE Hopper::GetFlapState() { return state; }
