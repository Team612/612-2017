#include "Hopper.h"
#include "../RobotMap.h"
Hopper::Hopper() :
    frc::Subsystem("Hopper") {

}

void Hopper::InitDefaultCommand() {

}
void Hopper::ShiftUp(){
    RobotMap::hopper->Set(DoubleSolenoid::Value::kForward);
}

void Hopper::ShiftDown(){
    RobotMap::hopper->Set(DoubleSolenoid::Value::kReverse);
}

void Hopper::ShiftOff(){
    RobotMap::hopper->Set(DoubleSolenoid::Value::kOff);
}
