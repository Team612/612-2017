#include "Shoot.h"
#include "../../Robot.h"

Shoot::Shoot(): Command() {
        // Use requires() here to declare subsystem dependencies
    // eg. requires(Robot::chassis.get());
    printf("Shoot constructor\n");
    Requires(Robot::shooter.get());
}

// Called just before this Command runs the first time
void Shoot::Initialize() {
    printf("Shoot init\n");
    Robot::shooter->Spin(-IDLE);
}

// Called repeatedly when this Command is scheduled to run
void Shoot::Execute() {
    if (-Robot::oi->getgunner()->GetY(frc::GenericHID::kLeftHand) > 0.1) {
        if (Robot::oi->getdriver()->GetStartButton())
            Robot::shooter->Spin(START_MULTIPLIER * OPTIMAL_RPM);
        else
            Robot::shooter->Spin(OPTIMAL_RPM);
        //Robot::shooter->Agitate();
    } else {
        Robot::shooter->Spin(-IDLE);
    }

}

// Make this return true when this Command no longer needs to run execute()
bool Shoot::IsFinished() {
    return false;
}

// Called once after isFinished returns true
void Shoot::End() {
    printf("Info: Shoot ended\n");
    Robot::shooter->Spin(0.0f);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void Shoot::Interrupted() {
    printf("Warning: Shoot Interrupted!\n");
    Robot::shooter->Spin(0.0f);
}
