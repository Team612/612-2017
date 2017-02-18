#include <Robot.h>
#include "AutoOneGear.h"

AutoOneGear::AutoOneGear(): PIDCommand("AutoTenBall", Robot::drivetrain->GetCurrentProfile()->P,
                                                      Robot::drivetrain->GetCurrentProfile()->I,
                                                      Robot::drivetrain->GetCurrentProfile()->D) {

    double DistancePerWheelRotation = pi*Robot::drivetrain->GetCurrentProfile()->WheelDiameter;
    double WheelRotationsPerPulse = Robot::drivetrain->GetCurrentProfile()->NativeToRPM *
                                    Robot::drivetrain->GetCurrentProfile()->EncoderToWheel * (60/0.1);
    double DistancePerPulse = DistancePerWheelRotation * WheelRotationsPerPulse;

    DISTANCE = DISTANCE_METERS / DistancePerPulse;

    Requires(Robot::drivetrain.get());

    GetPIDController()->SetContinuous(true); //?
    GetPIDController()->SetOutputRange(-1, 3);
    GetPIDController()->SetPercentTolerance(0.05);
}

void AutoOneGear::Initialize() {
    SetTimeout(15.0);
    leftInitialDistance = RobotMap::drive_ml->GetPosition();
    rightInitialDistance = RobotMap::drive_mr->GetPosition();
}

void AutoOneGear::Execute() {

}

bool AutoOneGear::IsFinished() {
    return IsTimedOut();
}

void AutoOneGear::End() {

    printf("Info: End auto one gear.\n");
    Robot::drivetrain->SetVelocity(0.0, 0.0);
}

void AutoOneGear::Interrupted() {
    printf("Info: AutoOneGear Interrupted.\n");
    Robot::drivetrain->SetVelocity(0.0, 0.0);
}

double AutoOneGear::ReturnPIDInput() {
    double AvgDist = ((RobotMap::drive_ml->GetPosition() - leftInitialDistance) +
                      (RobotMap::drive_mr->GetPosition() - rightInitialDistance))
                      / 2; //Average of both sides
    return AvgDist;
}

void AutoOneGear::UsePIDOutput(double output) {
    Robot::drivetrain->SetVelocity(output, output);
}
