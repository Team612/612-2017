#include "Grab.h"
#include "../../Robot.h"

Grab::Grab() : InstantCommand("Grab") {
    //TODO consider if this should require the subsystem
}

void Grab::Execute() {
    Robot::climber->Grab(1);
    frc::Wait(0.75);
}

void Grab::End() {
    Robot::climber->Grab(0);
}
