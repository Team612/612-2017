#include "IntakeFuel.h"

IntakeFuel::IntakeFuel() {
    Requires(Robot::intake.get());
}

void IntakeFuel::Initialize() {

}

void IntakeFuel::Execute() {
    //Drive team liked this when it was on soda
    if(Robot::oi->getgunner()->GetSmoothTrigger(frc::GenericHID::kRightHand) > 0.01) {
        if(Robot::oi->getgunner()->GetBumper(frc::GenericHID::kLeftHand))
            Robot::intake->ClearBalls();
        else
            Robot::intake->IntakeFuel();
    } else {
        Robot::intake->Stop();
    }
}

bool IntakeFuel::IsFinished() {
    return false;
}

void IntakeFuel::End() {
    Robot::intake->Stop();
}

void IntakeFuel::Interrupted() {
    Robot::intake->Stop();
}
