#include "DriveDistance.h"

/*! \brief Drives the robot a set distance, as specified in the constructor. */

/*! Partially configures the PID controller and converts the distance parameter into raw encoder units. */
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
/*! Records the initial position of the encoders and enables the PID. */
void DriveDistance::Initialize() {
    printf("DriveDistance init\n");

    leftInitialDistance = RobotMap::drive_ml->GetPosition();
    rightInitialDistance = RobotMap::drive_mr->GetPosition();

    GetPIDController()->SetSetpoint(distance);
    GetPIDController()->SetInputRange(0.0, distance);
    GetPIDController()->Enable();
}
/*! No function. */
void DriveDistance::Execute() {

}
/*! Returns true when the PID controller is on target. */
bool DriveDistance::IsFinished() {
    return GetPIDController()->OnTarget();
}
/*! Stops the drivetrain. */
void DriveDistance::End() {
    printf("Info: Completed DriveDistance");
    Robot::drivetrain->ThrottleByRPM(0.0, 0.0);
}
/*! Stops the drivetrain. */
void DriveDistance::Interrupted() {
    printf("Warning: DriveDistance interrupted!");
    Robot::drivetrain->ThrottleByRPM(0.0, 0.0);
}
/*! Returns the current distance from the starting point, in encoder units. */
double DriveDistance::ReturnPIDInput() {
    double AvgDist = ((RobotMap::drive_ml->GetPosition() - leftInitialDistance) +
                      (RobotMap::drive_mr->GetPosition() - rightInitialDistance))
                      / 2; //Average of both sides
    return AvgDist;
}
/*! Drives the drivetrain with the output of the PID controller. */
void DriveDistance::UsePIDOutput(double output) {
    Robot::drivetrain->ThrottleByRPM(output, output);
}
