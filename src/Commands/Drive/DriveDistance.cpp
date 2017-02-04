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

    leftInitialDistance = RobotMap::drivetrainleft_encoder->GetDistance();
    rightInitialDistance = RobotMap::drivetrainright_encoder->GetDistance();

    RobotMap::drive->ArcadeDrive(SPEED,0.0f);
}

void DriveDistance::Execute() {

}

bool DriveDistance::IsFinished() {
    double AvgDist = ((RobotMap::drivetrainleft_encoder->GetDistance() - leftInitialDistance) +
               (RobotMap::drivetrainright_encoder->GetDistance() - rightInitialDistance))
               / 2; //Average of both sides
    return AvgDist < distance;
}

void DriveDistance::End() {
    printf("Info: Completed DriveDistance");
    RobotMap::drive->ArcadeDrive(0.0f,0.0f);
}

void DriveDistance::Interrupted() {
    printf("Error: DriveDistance interrupted!");
    RobotMap::drive->ArcadeDrive(0.0f,0.0f);
}
