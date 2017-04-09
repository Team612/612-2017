#include "SetIntake.h"

#include "../../Robot.h"

SetIntake::SetIntake(bool clear) {
    //SetTimeout(timeout);
    this->clear = clear;
}

void SetIntake::Initialize() {

}

void SetIntake::Execute() {
    if(clear)
        Robot::intake->ClearBalls();
    else {
        Robot::intake->IntakeFuel();
    }
}

bool SetIntake::IsFinished() {
    //return IsTimedOut();
    return false;
}

void SetIntake::End() {
    Robot::intake->Stop();
}

void SetIntake::Interrupted() {
    Robot::intake->Stop();
}
