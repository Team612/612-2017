#include "AutoDrive.h"

AutoDrive::AutoDrive(double time) {

}

void AutoDrive::Initialize() {

}

void AutoDrive::Execute() {
  RobotMap::drive-> ArcadeDrive(1,0);
//argument for num of seconds moving forward
//if statement checks if timer has exceeded that time, if so then stop motors & reset timer object
}

bool AutoDrive::IsFinished() {
    return IsTimedOut();
}

void AutoDrive::End() {

}

void AutoDrive::Interrupted() {

}
