#include <Robot.h>
#include "AutoDrive.h"

AutoDrive::AutoDrive(float time, float speed) {

    _time = time; //sets timeout time equal to the time inputted (seconds)
    _speed = speed; //sets drive speed equal to speed inputted
    SetTimeout((double)time);
    Requires(Robot::drivetrain.get());
}

void AutoDrive::Initialize() {
    Robot::drivetrain->TankDrive(_speed * .92, _speed);
}

void AutoDrive::Execute() {

}

bool AutoDrive::IsFinished() {
    return IsTimedOut();
}

void AutoDrive::End() {

    printf("Info: End auto driving.\n");
    Robot::drivetrain->SetVelocity(0.0, 0.0);
}

void AutoDrive::Interrupted() {
    printf("Info: AutoDrive Interrupted.\n");
    Robot::drivetrain->SetVelocity(0.0, 0.0);
}
