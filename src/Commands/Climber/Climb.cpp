#include "Climb.h"

Climb::Climb(): Command() {

}

void Climb::Initialize() {

}

void Climb::Execute() {
    Robot::climber->Climb(0.4f);
}

bool Climb::IsFinished() {
    return false;
}

void Climb::End() {

}

void Climb::Interrupted() {

}
