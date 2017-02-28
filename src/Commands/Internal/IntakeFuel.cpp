#include "IntakeFuel.h"

IntakeFuel::IntakeFuel(bool intake) {
    in = intake;
    Requires(Robot::intake.get());
}

void IntakeFuel::Initialize() {

}

void IntakeFuel::Execute() {
    if(in)
        Robot::intake->IntakeFuel();
    else
        Robot::intake->ClearBalls();
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
