#include "Grab.h"
#include "../../Robot.h"

Grab::Grab() : Command("Grab") {
    //TODO consider if this should require the subsystem
}

void Grab::Initialize() {

}

void Grab::Execute() {
    Robot::climber->Grab(1);
    frc::Wait(0.75);
}

bool Grab::IsFinished() {
    return true;
}

void Grab::End() {
    Robot::climber->Grab(0);
}

void Grab::Interrupted() {
    Robot::climber->Grab(0);
}
