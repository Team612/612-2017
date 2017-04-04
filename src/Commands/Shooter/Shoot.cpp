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
    //frc::SmartDashboard::PutNumber("Shooter Setpoint", 1000);
    Robot::shooter->Spin(0.0f);
}

// Called repeatedly when this Command is scheduled to run
void Shoot::Execute() {
	printf("Shoot Execute\n");
    if(Robot::oi->getgunner()->GetAButton()) {
          auto b = static_cast<float>(Robot::oi->getgunner()->GetSmoothY(frc::GenericHID::kLeftHand));
          // If the joystick is not up or not greater than the dead band
          if (!(std::abs(b) > DEADBAND && b < 0))
              b = 0.0f;
          // at this stage, b should be negative, so b * a positive throttle makes the shooter go faster
          // in the negative direction
          Robot::shooter->Spin(OPTIMAL_RPM + b * THROTTLE);
    } else
        Robot::shooter->Spin(IDLE);
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
