#include "Shooter.h"
#include "../RobotMap.h"
#include "../Commands/Shooter/Shoot.h"

Shooter::Shooter() : Subsystem("Shooter") {
    //talon = RobotMap::talon_shoot;
}

void Shooter::InitDefaultCommand() {
    SetDefaultCommand(new Shoot());
}
