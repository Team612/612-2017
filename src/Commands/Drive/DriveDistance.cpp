#include "DriveDistance.h"

//Drive a certain distance.
//This command requires both drivetrain encoders to have SetDistancePerPulse() be properly set.
DriveDistance::DriveDistance(double distance): Command() { //Should the distance input be in initialize?
    printf("DriveDistance constructor\n");                 //Becuase IDK if we can call it again with a new distance mid-match
    this->distance = distance;
}

void DriveDistance::Initialize() {
    printf("DriveDistance init\n");
    Requires(Robot::drivetrain.get());

    leftInitialDistance = drivetrainleft_encoder->GetDistance();
    rightInitialDistance = drivetrainright_encoder->GetDistance();

    RobotMap::drive->ArcadeDrive(SPEED,0.0f);
}

void DriveDistance::Execute() {

}

bool DriveDistance::IsFinished() {
    AvgDist = ((drivetrainleft_encoder->GetDistance() - leftInitialDistance) +
               (drivetrainright_encoder->GetDistance() - rightInitialDistance))
               / 2; //Average of both sides
    return AvgDist < distance;
}

void DriveDistance::End() {
    printf("Info: Completed a DriveDistance of " + distance);
    RobotMap::drive->ArcadeDrive(0.0f,0.0f);
}

void DriveDistance::Interrupted() {
    AvgDist = ((drivetrainleft_encoder->GetDistance() - leftInitialDistance) +
               (drivetrainright_encoder->GetDistance() - rightInitialDistance))
               / 2;
    printf("Error: DriveDistance interrupted! Covered a distance of " + AvgDist);
    RobotMap::drive->ArcadeDrive(0.0f,0.0f);
}
