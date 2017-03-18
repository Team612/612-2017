/*
 * AutoDriveEncEnc.cpp
 *
 *  Created on: Mar 17, 2017
 *      Author: robouser
 */

#include <Commands/Autonomous/AutoDriveEnc.h>

#include <Robot.h>

AutoDriveEnc::AutoDriveEnc(float distance, float speed) {

    _distance = distance;
    _speed = speed;
    SetTimeout(5.0);
    Requires(Robot::drivetrain.get());
}

void AutoDriveEnc::Initialize() {
    Robot::drivetrain->TankDrive(_speed, _speed);
}

void AutoDriveEnc::Execute() {

}

bool AutoDriveEnc::IsFinished() {
    return IsTimedOut() || Robot::drivetrain->drive_ml->GetEncPosition();
}

void AutoDriveEnc::End() {

    printf("Info: End auto driving.\n");
    Robot::drivetrain->SetVelocity(0.0, 0.0);
}

void AutoDriveEnc::Interrupted() {
    printf("Info: AutoDriveEnc Interrupted.\n");
    Robot::drivetrain->SetVelocity(0.0, 0.0);
}
