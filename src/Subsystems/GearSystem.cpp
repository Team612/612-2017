#include "GearSystem.h"
#include "RobotMap.h"

//TODO check to make sure kReverse is closed and kForward is open

GearSystem::GearSystem() : Subsystem("GearSystem") {
    actuator = RobotMap::gear_actuator;
    actuator->Set(DoubleSolenoid::Value::kReverse);
}

void GearSystem::InitDefaultCommand() {
    //TODO
}

void GearSystem::GearOpen() {
    actuator->Set(DoubleSolenoid::Value::kForward);
    state = GearState::OPEN;
}

void GearSystem::GearClose() {
    actuator->Set(DoubleSolenoid::Value::kReverse);
    state = GearState::CLOSED;
}

GearState GearSystem::GetGearState() { return state; }
