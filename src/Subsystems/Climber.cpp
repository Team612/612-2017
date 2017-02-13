#include "Climber.h"
#include "../RobotMap.h"

Climber::Climber() : Subsystem("Climber") {
    
}

void Climber::InitDefaultCommand() {

}

void Climber::Climb(float speed) {
    RobotMap::climber->Set(speed);
}
