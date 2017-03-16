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
    Robot::drivetrain->TankDrive((dir * 0.4), -(dir * 0.4));
}

bool HorizontalFind::IsFinished() {
	if(std::abs(Robot::oi->getdriver()->GetSmoothY(frc::GenericHID::kLeftHand)) > 0.01 ||
	   std::abs(Robot::oi->getdriver()->GetSmoothY(frc::GenericHID::kRightHand)) > 0.01 ||
	   Robot::oi->getgunner()->GetYButton()) {
		std::cout  << "Warning: Auto Align interrupted by drive!" << std::endl;
		return true;
	}
	return Robot::vision->GetTargetAmount() > 0;
}

void HorizontalFind::End() {
    Robot::drivetrain->TankDrive(0, 0);
}

void HorizontalFind::Interrupted() {
    Robot::drivetrain->TankDrive(0, 0);
}
