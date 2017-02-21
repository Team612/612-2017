#include "MoveToTarget.h"

MoveToTarget::MoveToTarget(int dist) : PIDCommand("MoveToTarget", 0.0001, 0, 0) {
	//ur(1, 2);
	this->dist = dist;
	this->GetPIDController()->SetSetpoint(dist);
	auto pid = GetPIDController();
	pid->Enable();
}

// Called just before this Command runs the first time
void MoveToTarget::Initialize() {

}

// Called repeatedly when this Command is scheduled to run
void MoveToTarget::Execute() {
	auto pid = GetPIDController();
	this->GetPIDController()->SetSetpoint(SmartDashboard::GetNumber("UR DIST", 1000));
	MIN_OUTPUT = SmartDashboard::GetNumber("MIN OUTPUT", 0);
	pid->SetOutputRange(MIN_OUTPUT - 1, 1 - MIN_OUTPUT);
	pid->SetPID(SmartDashboard::GetNumber("UR P", 0.0001), SmartDashboard::GetNumber("UR I", 0), SmartDashboard::GetNumber("UR D", 0));
}

// Make this return true when this Command no longer needs to run execute()
bool MoveToTarget::IsFinished() {
	//return this->GetPIDController()->OnTarget();
	return false;
}

// Called once after isFinished returns true
void MoveToTarget::End() {

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void MoveToTarget::Interrupted() {
	Robot::drivetrain->Throttle(0,0);
}

double MoveToTarget::ReturnPIDInput() {
	std::printf("test");
	return Robot::drivetrain->GetURCenter()->GetRangeMM();
}

void MoveToTarget::UsePIDOutput(double output) {
	if (output < 0)
		output -= MIN_OUTPUT;
	else
		output += MIN_OUTPUT;

	SmartDashboard::PutNumber("PID Output", output);

	Robot::drivetrain->Throttle(output, output);
}
