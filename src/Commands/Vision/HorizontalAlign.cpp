#include "HorizontalAlign.h"

HorizontalAlign::HorizontalAlign(float timeout, bool continuous) :
		PIDCommand("AlignToTarget", 0.004, 0, 0)
{
	Requires(Robot::drivetrain.get());
	SetTimeout(8);

	this->continuous = continuous;

	if(timeout != 0)
		SetTimeout(timeout);
}

void HorizontalAlign::Initialize()
{
	printf("test");
	auto pid = GetPIDController();
	pid->SetAbsoluteTolerance(40);
	pid->SetSetpoint(SCREEN_CENTER_X); //Point we're trying to get to
	pid->Disable();
	pid->SetOutputRange(-(ROT_SPEED_CAP - ROT_SPEED_MIN), ROT_SPEED_CAP - ROT_SPEED_MIN);
}

void HorizontalAlign::Execute()
{
	//Only if we need to FIND a target
	if (!hasTarget)
	{
        Robot::drivetrain->ThrottleByRPM(-1 * lastTargetDir, 1 * lastTargetDir);
		hasTarget = Robot::vision->UpdateCurrentTarget();
	}
	else
	{
		if (!GetPIDController()->IsEnabled())
		{
			PIDUserDisabled = false;
			//GetPIDController()->SetPID(1, 0, 0);
			auto pid = GetPIDController();
			pid->SetPID(SmartDashboard::GetNumber("dP", 0.004), SmartDashboard::GetNumber("dI", 0), SmartDashboard::GetNumber("dD", 0));
			pid->Enable();
		}
		else
			printf("PID Enabled\n");
	}
}

//Inherited from PID Command, returns the input from the vision targets
double HorizontalAlign::ReturnPIDInput()
{
	//Makes sure that the target still exists, if not, it goes bye bye
	std::shared_ptr<VisionTarget> target = Robot::vision->GetTrackedGoal();
	if (target == nullptr)
	{
		PIDUserDisabled = true;
		hasTarget = false;
		GetPIDController()->Disable();
		return 0;
	}
	else
	{
		int centerX = target->GetCenter().x;
		printf("Center X %u\n", centerX);

		lastTargetDir = centerX < SCREEN_CENTER_X?-1:1;
		lastCenter = centerX;

		return (double) centerX;
	}
}

void HorizontalAlign::UsePIDOutput(double output)
{
	if (GetPIDController()->OnTarget())
	{
		onTargetCounter++;
		if (onTargetCounter > 10) {
			aligned = true;
            Robot::drivetrain->ThrottleByRPM(0, 0);
			return;
		}
	}
	else
	{
		onTargetCounter = 0;
	}

	SmartDashboard::PutNumber("OnTarget Counter", onTargetCounter);

	printf("%f", output);

	if (output > 0)
		output += ROT_SPEED_MIN;
	else if (output < 0)
		output -= ROT_SPEED_MIN;

	if (!PIDUserDisabled && !IsFinished())
        Robot::drivetrain->ThrottleByRPM(output, -output);
	//printf("\noutput");

	SmartDashboard::PutNumber("AutoAlign Output", output);

	printf("wowowow %f, %u\n" , output, PIDUserDisabled);
}

bool HorizontalAlign::IsFinished()
{
	return !continuous && aligned;
}

void HorizontalAlign::End()
{
	GetPIDController()->Disable();
    Robot::drivetrain->ThrottleByRPM(0, 0);
}

void HorizontalAlign::Interrupted()
{
	GetPIDController()->Disable();
    Robot::drivetrain->ThrottleByRPM(0, 0);
}
