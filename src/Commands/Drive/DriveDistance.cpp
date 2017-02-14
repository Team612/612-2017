#include "DriveDistance.h"

//Drive a certain distance.
//This command requires both drivetrain encoders to have SetDistancePerPulse() be properly set.
DriveDistance::DriveDistance(double distance): PIDCommand("DriveDistance", 0.2, 0.0, 0.0) {
    printf("DriveDistance constructor\n");
    this->distance = distance;

    GetPIDController()->SetContinuous(true); //?
    GetPIDController()->SetOutputRange(-Robot::drivetrain->GetCurrentProfile()->WheelMaxRPM, Robot::drivetrain->GetCurrentProfile()->WheelMaxRPM);
    GetPIDController()->SetPercentTolerance(0.05);
}

void DriveDistance::Initialize() {
    printf("DriveDistance init\n");
    Requires(Robot::drivetrain.get());

    leftInitialDistance = RobotMap::drive_ml->GetPosition();
    rightInitialDistance = RobotMap::drive_mr->GetPosition();

    GetPIDController()->SetSetpoint(distance);
    GetPIDController()->SetInputRange(0.0, distance);
    GetPIDController()->Enable();
}

void DriveDistance::Execute() {

}

bool DriveDistance::IsFinished() {
    return GetPIDController()->OnTarget();
}

void DriveDistance::End() {
    printf("Info: Completed DriveDistance");
    Robot::drivetrain->SetVelocity(0.0f, 0.0f);
}

void DriveDistance::Interrupted() {
    printf("Warning: DriveDistance interrupted!");
    Robot::drivetrain->SetVelocity(0.0f, 0.0f);
}

double DriveDistance::ReturnPIDInput() {
    double AvgDist = ((RobotMap::drive_ml->GetPosition() - leftInitialDistance) +
                      (RobotMap::drive_mr->GetPosition() - rightInitialDistance))
                      / 2; //Average of both sides
    return AvgDist;
}

void DriveDistance::UsePIDOutput(double output) {
    Robot::drivetrain->SetVelocity(output, output);
}
