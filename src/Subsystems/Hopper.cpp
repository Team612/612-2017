#include "Hopper.h"

Hopper::Hopper() :
    frc::Subsystem("Hopper") {

}

void Hopper::InitDefaultCommand() {

}
void Shifter::ShiftUp(){
    RobotMap::hopper->Set(DoubleSolenoid::Value::kForward);
}

void Shifter::ShiftDown(){
    RobotMap::hopper->Set(DoubleSolenoid::Value::kReverse);
}

void Shifter::ShiftOff(){
    RobotMap::hopper->Set(DoubleSolenoid::Value::kOff);
}
