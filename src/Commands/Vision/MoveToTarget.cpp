#include "MoveToTarget.h"
#include "Robot.h"

MoveToTarget::MoveToTarget(int dist) : PIDCommand("MoveToTarget", 0.0001, 0, 0, 0.5) {
    //ur(1, 2);
    this->dist = dist;
    GetPIDController()->SetOutputRange(-1.0, 1.0);
    GetPIDController()->SetSetpoint(dist);
    GetPIDController()->Enable();
    GetPIDController()->SetAbsoluteTolerance(2.0); //we're good if we're within 2 inches
    Requires(Robot::drivetrain.get());
}

// Called just before this Command runs the first time
void MoveToTarget::Initialize() {

}

// Called repeatedly when this Command is scheduled to run
void MoveToTarget::Execute() {
    //this->GetPIDController()->SetSetpoint(SmartDashboard::GetNumber("UR DIST", 1000));
    //MIN_OUTPUT = SmartDashboard::GetNumber("MIN OUTPUT", 0);
    //GetPIDController()->SetPID(SmartDashboard::GetNumber("UR P", 0.0001), SmartDashboard::GetNumber("UR I", 0), SmartDashboard::GetNumber("UR D", 0), SmartDashboard::GetNumber("UR F", 0.5));
    Robot::drivetrain->TankDrive(current_power, current_power);
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
    Robot::drivetrain->TankDrive(0, 0);
}

double MoveToTarget::ReturnPIDInput() {

    return Robot::drivetrain->GetURSide()->GetDistanceInches();
}

void MoveToTarget::UsePIDOutput(double output) {

    SmartDashboard::PutNumber("PID Output - Drive distance", output);
    current_power = output;
}
