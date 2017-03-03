#include "MoveToTarget.h"
#include "Robot.h"

MoveToTarget::MoveToTarget(int dist) : PIDCommand("MoveToTarget", 0.0001, 0, 0, 0.5) {
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
	//this->GetPIDController()->SetSetpoint(SmartDashboard::GetNumber("UR DIST", 1000));
	//MIN_OUTPUT = SmartDashboard::GetNumber("MIN OUTPUT", 0);
	pid->SetOutputRange(-1.0, 1.0);
	pid->SetPID(SmartDashboard::GetNumber("UR P", 0.0001), SmartDashboard::GetNumber("UR I", 0), SmartDashboard::GetNumber("UR D", 0), SmartDashboard::GetNumber("UR F", 0.5));
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
    Robot::drivetrain->ThrottleByRPM(0, 0);
}

double MoveToTarget::ReturnPIDInput() {
	//std::printf("MoveToTarget.cpp: Returning PID Input");
	return Robot::drivetrain->GetURCenter()->GetRangeMM();
}

void MoveToTarget::UsePIDOutput(double output) {
	/*if (output < 0)
		output -= MIN_OUTPUT;
	else
		output += MIN_OUTPUT;*/

	SmartDashboard::PutNumber("PID Output - Drive distance", output);
	//std::cout << "MoveToTarget.cpp: Setting output" << std::endl;
    //Robot::drivetrain->TankDrive(output, output); //see how well this works before going full PID
}
