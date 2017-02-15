#include <Robot.h>
#include "AutoTenBall.h"

AutoTenBall::AutoTenBall(): PIDCommand("AutoTenBall", Robot::drivetrain->GetCurrentProfile()->P,
                                                      Robot::drivetrain->GetCurrentProfile()->I,
                                                      Robot::drivetrain->GetCurrentProfile()->D) {
    SetTimeout(10000); // Placeholder until stage3FirstRun
    Requires(Robot::drivetrain.get());
    Requires(Robot::shooter.get());
    stage1 = false;
    stage2 = false;
    stage2FirstRun = false;
    stage3 = false;
    stage3FirstRun = false;

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
    GetPIDController()->SetInputRange(0.0, DISTANCE);
    GetPIDController()->Enable();
}

void AutoTenBall::Execute() {
    if (stage1) return;
    else if (stage2) {
        if (stage2FirstRun){

            stage2FirstRun = false;
        }
    }
    else if (stage3) {
        if (stage3FirstRun) {
            RobotMap::shooter->Set(OPTIMAL_RPM);

            SetTimeout(SHOOT_TIME);
            GetPIDController()->Disable();
            stage3FirstRun = false;
        }
    }
}

bool AutoTenBall::IsFinished() {
    return IsTimedOut();
}

void AutoTenBall::End() {
    printf("Info: End AutoTenBall.\n");
    Robot::drivetrain->SetVelocity(0.0, 0.0);
    RobotMap::shooter->Set(0.0);
}

void AutoTenBall::Interrupted() {
    printf("Warning: AutoTenBall Interrupted.\n");
    Robot::drivetrain->SetVelocity(0.0, 0.0);
    RobotMap::shooter->Set(0.0);
}

double AutoTenBall::ReturnPIDInput(); {
    if (GetPIDController()->OnTarget()) {
        if (stage1) {
            stage1 = false;
            stage2 = true;
            stage2FirstRun = true;
        } else if (stage2) {
            stage2 = false;
            stage3 = true;
        }
    }
    if (stage1) {
        double AvgDist = ((RobotMap::drive_ml->GetPosition() - leftInitialDistance) +
                          (RobotMap::drive_mr->GetPosition() - rightInitialDistance))
                          / 2; //Average of both sides
        return AvgDist;
    } else if (stage2) {
        double AvgDist = ((leftInitialDistance - RobotMap::drive_ml->GetPosition()) +
                          (RobotMap::drive_mr->GetPosition() - rightInitialDistance))
                          / 2; //Average of both sides
        return AvgDist;
    }
    else return 0.0;
}

void AutoTenBall::UsePIDOutput(double output) {
    if (stage1) Robot::drivetrain->SetVelocity(output, output);
    if (stage2) Robot::drivetrain->SetVelocity(-output, output);
    else Robot::drivetrain->SetVelocity(0,0);
}
