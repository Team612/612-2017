#include "GearSystem.h"
#include "RobotMap.h"

#include <thread>

//TODO check to make sure kReverse is closed and kForward is open

GearSystem::GearSystem() : Subsystem("GearSystem") {
    actuator = RobotMap::gear_actuator;
    actuator->Set(DoubleSolenoid::Value::kReverse);
    frc::Wait(0.5);
    actuator->Set(DoubleSolenoid::Value::kOff);
}

void GearSystem::InitDefaultCommand() {
    //TODO
}

void GearSystem::GearOpen() {
    actuator->Set(DoubleSolenoid::Value::kForward);
    state = GearState::OPEN;
    frc::Wait(0.5);
    actuator->Set(DoubleSolenoid::Value::kOff);
}

void GearSystem::GearClose() {
    actuator->Set(DoubleSolenoid::Value::kReverse);
    state = GearState::CLOSED;
    frc::Wait(0.5);
    actuator->Set(DoubleSolenoid::Value::kOff);
}

GearState GearSystem::GetGearState() { return state; }
