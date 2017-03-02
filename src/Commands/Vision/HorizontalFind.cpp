#include "HorizontalFind.h"
#include "../../Robot.h"

HorizontalFind::HorizontalFind(Direction d, float timeout) {
	Requires(Robot::drivetrain.get());
	Requires(Robot::vision.get());

	if (d == LEFT)
		dir = 1;
	else
		dir = -1;

	if (timeout != 0)
		SetTimeout(timeout);
}

void HorizontalFind::Initialize() { }

void HorizontalFind::Execute() {
	Robot::vision->PullValues();
    Robot::drivetrain->TankDrive(-(dir * 0.4), (dir * 0.4));
}

bool HorizontalFind::IsFinished() {
	return Robot::vision->GetTargetAmount() > 0;
}

void HorizontalFind::End() {
    Robot::drivetrain->TankDrive(0, 0);
}

void HorizontalFind::Interrupted() {
    Robot::drivetrain->TankDrive(0, 0);
}
