#include "Climb.h"

Climb::Climb(): Command() {
    Requires(Robot::climber.get());
}

void Climb::Initialize() {

}

void Climb::Execute() {
    //TODO Implement when reasonable threshold is found
    //TODO consider disabling all talons and climbing automatically
    /*if(abs(Robot::init_climber_current - RobotMap::pdp->GetCurrent(15)) > CURRENT_THRESHOLD) {
        Robot::climber->Block();
        return; //prevent controls
    }*/
    if(Robot::oi->getgunner()->GetSmoothY(frc::GenericHID::kRightHand) > 0.01)
        Robot::climber->Move(-static_cast<float>(Robot::oi->getgunner()->GetSmoothY(frc::GenericHID::kRightHand)));
    else
        Robot::climber->Block();
}


bool Climb::IsFinished() {
    return false;
}

void Climb::End() {
    Robot::climber->Block();
}

void Climb::Interrupted() {
    Robot::climber->Block();
}
