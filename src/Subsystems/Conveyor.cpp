#include "Conveyor.h"
#include "../RobotMap.h"

Conveyor::Conveyor() : Subsystem("Conveyor") {

}

void Conveyor::InitDefaultCommand() {

}

void Conveyor::Move(float speed) {
    RobotMap::conveyor_talon->Set(speed);
}
