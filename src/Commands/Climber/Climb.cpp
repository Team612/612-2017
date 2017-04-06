#include "Climb.h"

Climb::Climb(): Command() {
    Requires(Robot::climber.get());
}

void Climb::Initialize() {

}

void Climb::Execute() {
    if(Robot::oi->getgunner()->GetSmoothY(frc::GenericHID::kRightHand) < -0.01) {
        Robot::climber->Move(static_cast<float>(Robot::oi->getgunner()->GetY(frc::GenericHID::kRightHand)));
    }
    else {
        Robot::climber->Block();
    }
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
