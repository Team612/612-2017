#include "IntakeFuel.h"

IntakeFuel::IntakeFuel() {

}

void IntakeFuel::Initialize() {

}

void IntakeFuel::Execute() {
    Robot::intake->IntakeFuel(0.4f);
}

bool IntakeFuel::IsFinished() {
    return false;
}

void IntakeFuel::End() {

}

void IntakeFuel::Interrupted() {

}
