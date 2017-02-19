#include "Climb.h"

Climb::Climb(): Command() {
    Requires(Robot::climber.get());
}

void Climb::Initialize() {

}

void Climb::Execute() {
    //TODO Implement when reasonable threshold is found
    if(abs(Robot::init_climber_current - RobotMap::pdp->GetCurrent(15)) > CURRENT_THRESHOLD) {
        Robot::climber->Block();
        return; //prevent controls
    }
    if(Robot::oi->getgunner()->GetXButton())
        Robot::climber->Climb(1);
    else if(Robot::oi->getgunner()->GetYButton())
        Robot::climber->Climb(0.2);
    else
        Robot::climber->Block();
}


bool Climb::IsFinished() {
    return false;
}

void Climb::End() {

}

void Climb::Interrupted() {

}
