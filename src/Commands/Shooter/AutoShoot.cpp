#include "AutoShoot.h"
#include "../../Robot.h"

AutoShoot::AutoShoot(double timeout): Command() {
        // Use requires() here to declare subsystem dependencies
    // eg. requires(Robot::chassis.get());
    printf("AutoShoot constructor\n");
    Requires(Robot::shooter.get());
    this->timeout = timeout;
}

// Called just before this Command runs the first time
void AutoShoot::Initialize() {
    printf("AutoShoot init\n");
    SetTimeout(timeout);
    Robot::shooter->Spin(OPTIMAL_RPM);
}

// Called repeatedly when this Command is scheduled to run
void AutoShoot::Execute() {

}

// Make this return true when this Command no longer needs to run execute()
bool AutoShoot::IsFinished() {
    return IsTimedOut;
}

// Called once after isFinished returns true
void AutoShoot::End() {
    printf("Info: AutoShoot ended\n");
    Robot::shooter->Spin(0.0f);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void AutoShoot::Interrupted() {
    printf("Warning: AutoShoot Interrupted!\n");
    Robot::shooter->Spin(0.0f);
}
