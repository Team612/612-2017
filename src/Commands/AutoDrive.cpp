#include "AutoDrive.h"

AutoDrive::AutoDrive(float time) {

    SetTimeout((double)time);
}

void AutoDrive::Initialize() {
    RobotMap::drive-> ArcadeDrive(1,0);
}

void AutoDrive::Execute() {

}

bool AutoDrive::IsFinished() {
    return IsTimedOut();
}

void AutoDrive::End() {

    printf("Info: End auto driving.\n");
		RobotMap::drive-> ArcadeDrive(0,0);
}

void AutoDrive::Interrupted() {
		RobotMap::drive-> ArcadeDrive(0,0);
}
