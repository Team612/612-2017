#include "IntakeFuel.h"

IntakeFuel::IntakeFuel() {
    //in = intake;
    Requires(Robot::intake.get());
}

void IntakeFuel::Initialize() {

}

void IntakeFuel::Execute() {
    Robot::intake->IntakeFuel();
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
