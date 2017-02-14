#include "Climber.h"
#include "../RobotMap.h"
#include "lib612/Networking/Networking.h"

Climber::Climber() : Subsystem("Climber") {

}

void Climber::InitDefaultCommand() {

}


void Climber::Climb(float speed) {
    RobotMap::climber_talon_left->Set(speed);
    RobotMap::climber_talon_right->Set(speed);
    
}
