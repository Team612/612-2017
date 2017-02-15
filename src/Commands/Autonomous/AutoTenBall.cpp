#include <Robot.h>
#include "AutoTenBall.h"

AutoTenBall::AutoTenBall(): PIDCommand("AutoTenBall", Robot::drivetrain->GetCurrentProfile()->P,
                                                      Robot::drivetrain->GetCurrentProfile()->I,
                                                      Robot::drivetrain->GetCurrentProfile()->D) {
    SetTimeout((double)time);
    Requires(Robot::drivetrain.get());
    Requires(Robot::shooter.get());
    stage1 = false;
    stage2 = false;
    stage2FirstRun = false;
    stage3 = false;
    finished = false;

    GetPIDController()->SetContinuous(true); //?
    GetPIDController()->SetOutputRange(-1, 1);
    GetPIDController()->SetPercentTolerance(0.05);
}

void AutoTenBall::Initialize() {
    printf("Info: Init AutoTenBall.\n")
    stage1 = true;
    leftInitialDistance = RobotMap::drive_ml->GetPosition();
    rightInitialDistance = RobotMap::drive_mr->GetPosition();

    GetPIDController()->SetSetpoint(DISTANCE);
    GetPIDController()->SetINputRange(0.0, DISTANCE);
    GetPIDController()->Enable();
}

void AutoTenBall::Execute() {
    if (stage1) return;
    if (stage2) {
        if (stage2FirstRun){

            stage2FirstRun = false;
        }
    }
}

bool AutoTenBall::IsFinished() {
    return finished;
}

void AutoTenBall::End() {

    printf("Info: End AutoTenBall.\n");
    Robot::drivetrain->SetVelocity(0.0, 0.0);
    RobotMap::shooter->Set(0.0);
}

void AutoTenBall::Interrupted() {
    printf("Warning: AutoTenBall Interrupted.\n");
    Robot::drivetrain->SetVelocity(0.0, 0.0);
}

double AutoTenBall::ReturnPIDInput(); {
    if (stage1) return 0.0;
    else if (stage2) return 0.0;
    else return 0.0;
}

void AutoTenBall::UsePIDOutput(double output) {
    if (stage1) Robot::drivetrain->SetVelocity(output, output);
}
