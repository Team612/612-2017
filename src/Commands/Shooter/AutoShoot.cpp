#include "AutoShoot.h"
#include "../../Robot.h"
// A duplicate of Shoot() which does not require user input, for use during Autonomous.
AutoShoot::AutoShoot(): Command() {
        // Use requires() here to declare subsystem dependencies
    // eg. requires(Robot::chassis.get());
    Requires(Robot::shooter.get());
}

// Called just before this Command runs the first time
void Shoot::Initialize() {

}

// Called repeatedly when this Command is scheduled to run
void Shoot::Execute() {

}

// Make this return true when this Command no longer needs to run execute()
// Proposed function: Shoot until the container is empty
bool Shoot::IsFinished() {
    return false;
}

// Called once after isFinished returns true
void Shoot::End() {

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void Shoot::Interrupted() {

}
