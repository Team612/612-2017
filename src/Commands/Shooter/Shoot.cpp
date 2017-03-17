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
    frc::SmartDashboard::PutNumber("Shooter Setpoint", 1000);
    Robot::shooter->Spin(0);
}

// Called repeatedly when this Command is scheduled to run
void Shoot::Execute() {
    if (-Robot::oi->getgunner()->GetY(frc::GenericHID::kLeftHand) > 0.02) {
        if (Robot::oi->getgunner()->GetStartButton())
            Robot::shooter->Spin(OPTIMAL_RPM * START_MULTIPLIER);
        else
            Robot::shooter->Spin(OPTIMAL_RPM);
    } else {
        Robot::shooter->Spin(IDLE);
    }
}

// Make this return true when this Command no longer needs to run execute()
bool Shoot::IsFinished() {
    return false;
}

// Called once after isFinished returns true
void Shoot::End() {
    printf("Info: Shoot ended\n");
    RobotMap::shooter_l->SetTalonControlMode(CANTalon::TalonControlMode::kThrottleMode);
    Robot::shooter->Spin(0.0f);
    RobotMap::shooter_l->SetTalonControlMode(CANTalon::TalonControlMode::kSpeedMode);
    RobotMap::shooter_l->SetFeedbackDevice(CANTalon::FeedbackDevice::CtreMagEncoder_Relative);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void Shoot::Interrupted() {
    printf("Warning: Shoot Interrupted!\n");
    RobotMap::shooter_l->SetTalonControlMode(CANTalon::TalonControlMode::kThrottleMode);
    Robot::shooter->Spin(0.0f);
    RobotMap::shooter_l->SetTalonControlMode(CANTalon::TalonControlMode::kSpeedMode);
    RobotMap::shooter_l->SetFeedbackDevice(CANTalon::FeedbackDevice::CtreMagEncoder_Relative);
}
