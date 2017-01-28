#include "AutoDrive.h"

AutoDrive::AutoDrive(float time, float speed) {

    _time = time; //sets timeout time equal to the time inputted (seconds)
    _speed = speed; //sets drive speed equal to speed inputted
    SetTimeout((double)time);
}

void AutoDrive::Initialize() {
    RobotMap::drive->ArcadeDrive(_speed,0.0f);
}

void AutoDrive::Execute() {

}

bool AutoDrive::IsFinished() {
    return IsTimedOut();
}

void AutoDrive::End() {

    printf("Info: End auto driving.\n");
    RobotMap::drive->ArcadeDrive(0.0f,0.0f);
}

void AutoDrive::Interrupted() {
    printf("Info: AutoDrive Interrupted.\n");
    RobotMap::drive->ArcadeDrive(0.0f,0.0f);
}
