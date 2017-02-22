#include "AutoIntake.h"

AutoIntake::AutoIntake(double timeout) {
    Requires(Robot::intake.get());
    this->timeout = timeout;
}

void AutoIntake::Initialize() {
    SetTimeout(timeout);
    Robot::intake->SetIntake(1.0f);
}

void AutoIntake::Execute() {

}

bool AutoIntake::IsFinished() {
    return IsTimedOut;
}

void AutoIntake::End() {
    Robot::intake->Stop();
}

void AutoIntake::Interrupted() {
    Robot::intake->Stop();
}
