#include "AutoDrive.h"

AutoDrive::AutoDrive(float time, float speed) {

    myTime = time;
    mySpeed = speed;
    SetTimeout((double)time);
}

void AutoDrive::Initialize() {
    RobotMap::drive-> ArcadeDrive(mySpeed,0.0f);
}

void AutoDrive::Execute() {

}

bool AutoDrive::IsFinished() {
    return IsTimedOut();
}

void AutoDrive::End() {

    printf("Info: End auto driving.\n");
		RobotMap::drive-> ArcadeDrive(0.0f,0.0f);
}

void AutoDrive::Interrupted() {
		RobotMap::drive-> ArcadeDrive(0.0f,0.0f);
}
