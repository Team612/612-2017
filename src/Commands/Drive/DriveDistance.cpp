#include "DriveDistance.h"

//Drive a certain distance. Input meters.
DriveDistance::DriveDistance(double distance): PIDCommand("DriveDistance", 0.2, 0.0, 0.0) {
    printf("DriveDistance constructor\n");

    //Assists calculations
    double DistancePerWheelRotation = pi*Robot::drivetrain->GetCurrentProfile()->WheelDiameter;
    double WheelRotationsPerPulse = Robot::drivetrain->GetCurrentProfile()->NativeToRPM *
                                    Robot::drivetrain->GetCurrentProfile()->EncoderToWheel * (60/0.1);
    double DistancePerPulse = DistancePerWheelRotation * WheelRotationsPerPulse;

    this->distance = distance / DistancePerPulse;

    GetPIDController()->SetContinuous(true); //?
    GetPIDController()->SetOutputRange(-MAX_THROTTLE, MAX_THROTTLE);
    GetPIDController()->SetPercentTolerance(0.05);
    Requires(Robot::drivetrain.get());
}

void DriveDistance::Initialize() {
    printf("DriveDistance init\n");

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
    Robot::drivetrain->ThrottleByRPM(0.0, 0.0);
}

void DriveDistance::Interrupted() {
    printf("Warning: DriveDistance interrupted!");
    Robot::drivetrain->ThrottleByRPM(0.0, 0.0);
}

double DriveDistance::ReturnPIDInput() {
    double AvgDist = ((RobotMap::drive_ml->GetPosition() - leftInitialDistance) +
                      (RobotMap::drive_mr->GetPosition() - rightInitialDistance))
                      / 2; //Average of both sides
    return AvgDist;
}

void DriveDistance::UsePIDOutput(double output) {
    Robot::drivetrain->ThrottleByRPM(output, output);
}
