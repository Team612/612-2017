#include "HorizontalAlign.h"

HorizontalAlign::HorizontalAlign(float timeout, bool continuous) :
        PIDCommand("AlignToTarget", 0.003, 0.0, 0.0) {
    //0.0006
    Requires(Robot::drivetrain.get());

    this->continuous = continuous;
    this->hasTarget = Robot::vision->UpdateCurrentTarget();

    if(timeout != 0)
        SetTimeout(timeout);
    //SmartDashboard::PutNumber("dP", 0.004); SmartDashboard::PutNumber("dI",0.0); SmartDashboard::PutNumber("dD", 0.0);
}

void HorizontalAlign::Initialize() {
    printf("Horizontal Align initialize\n");
    auto pid = GetPIDController();
    //pid->SetAbsoluteTolerance(PIXEL_TOLERANCE);
    pid->SetTolerance(PERCENT_TOLERANCE);
    pid->SetSetpoint(SCREEN_CENTER_X); //Point we're trying to get to
    pid->SetOutputRange(-(ROT_SPEED_CAP - ROT_SPEED_MIN), ROT_SPEED_CAP - ROT_SPEED_MIN);
    pid->Disable();
}

void HorizontalAlign::Execute() {
    //Only if we need to FIND a target
    hasTarget = Robot::vision->UpdateCurrentTarget();
    if (!hasTarget) {
        SmartDashboard::PutBoolean("Vision has target", hasTarget);
        Robot::drivetrain->TankDrive(-0.1 * lastTargetDir, 0.1 * lastTargetDir);
        hasTarget = Robot::vision->UpdateCurrentTarget();
    }
    else {
        if (!GetPIDController()->IsEnabled()) {
            PIDUserDisabled = false;
            //GetPIDController()->SetPID(1, 0, 0);
            auto pid = GetPIDController();
            //pid->SetPID(SmartDashboard::PutNumber("dP", 0.004), SmartDashboard::PutNumber("dI",0.0), SmartDashboard::PutNumber("dD", 0.0));
            pid->Enable();
        }
        else
            printf("Info: Vision PID Enabled\n");
    }
}

//Inherited from PID Command, returns the input from the vision targets
double HorizontalAlign::ReturnPIDInput() {
    //Makes sure that the target still exists, if not, it goes bye bye
    std::shared_ptr<VisionTarget> target = Robot::vision->GetTrackedGoal();
    if (target == nullptr) {
        PIDUserDisabled = true;
        hasTarget = false;
        GetPIDController()->Disable();
        return 0;
    }
    else {
        int centerX = target->GetCenter().x;
        SmartDashboard::PutNumber("Vision Center", target->GetCenter().x);
        printf("Center X %u\n", centerX);

        lastTargetDir = centerX < SCREEN_CENTER_X?-1:1;
        lastCenter = centerX;

        return (double) centerX;
    }
}

void HorizontalAlign::UsePIDOutput(double output) {
    if (GetPIDController()->OnTarget()) {
        onTargetCounter++;
        if (onTargetCounter > TICK_TOLERANCE) {
            aligned = true;
            Robot::drivetrain->TankDrive(0, 0);
            return;
        }
    }
    else {
        onTargetCounter = 0;
    }

    SmartDashboard::PutNumber("OnTarget Counter", onTargetCounter);

    printf("%f", output);

    if (output > 0)
        output += ROT_SPEED_MIN;
    else if (output < 0)
        output -= ROT_SPEED_MIN;

    if (!PIDUserDisabled && !IsFinished())
        Robot::drivetrain->TankDrive(-output, output); //camera is upside down
    //printf("\noutput");

    SmartDashboard::PutNumber("AutoAlign Output", output);
    printf("wowowow %f, %u\n" , output, PIDUserDisabled);
}

bool HorizontalAlign::IsFinished() {
    if(IsTimedOut()) {
        std::cout << "Warning: Horizontal Align timed out without full alignment!" << std::endl;
        return true;
    }
    if(std::abs(Robot::oi->getdriver()->GetSmoothY(frc::GenericHID::kLeftHand)) > 0.01 ||
            std::abs(Robot::oi->getdriver()->GetSmoothY(frc::GenericHID::kRightHand)) > 0.01 ||
            Robot::oi->getgunner()->GetYButton()) {
        std::cout  << "Warning: Auto Align interrupted by drive!" << std::endl;
        return true;
    }
    return !continuous && aligned;
}

void HorizontalAlign::End() {
    GetPIDController()->Disable();
    Robot::drivetrain->TankDrive(0, 0);
}

void HorizontalAlign::Interrupted() {
    GetPIDController()->Disable();
    Robot::drivetrain->TankDrive(0, 0);
}
