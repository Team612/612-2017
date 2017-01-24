#include "MPDrive.h"
#include "../Robot.h"

MPDrive::MPDrive(int profile): Command() {

}

void MPDrive::Initialize() {
    RobotMap::drive_fl->SetTalonControlMode(CANTalon::kMotionProfileMode);
    RobotMap::drive_fr->SetTalonControlMode(CANTalon::kMotionProfileMode);
}

void MPDrive::Execute() {
}

bool MPDrive::IsFinished() {
    return false;
}

void MPDrive::End() {

}

void MPDrive::Interrupted() {
    this->End();
}
