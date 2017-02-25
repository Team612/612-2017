#include "Shifter.h"
#include "../RobotMap.h"

Shifter::Shifter() :
    frc::Subsystem("Shifter") {

}

void Shifter::InitDefaultCommand() {

}

void Shifter::ShiftUp(){
    RobotMap::shifter->Set(DoubleSolenoid::Value::kForward);
}

void Shifter::ShiftDown(){
    RobotMap::shifter->Set(DoubleSolenoid::Value::kReverse);
}

void Shifter::ShiftOff(){
    RobotMap::shifter->Set(DoubleSolenoid::Value::kOff);
}
