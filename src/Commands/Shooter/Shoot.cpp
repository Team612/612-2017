#include "Shoot.h"
#include "../../Robot.h"

Shoot::Shoot(): Command() {
        // Use requires() here to declare subsystem dependencies
    // eg. requires(Robot::chassis.get());
    printf("Shoot constructor\n");
    Requires(Robot::shooter.get());
    RobotMap::shooter_l->SetPID(0.22, 0, 0, 0.1097);
    //get values from connected cimcoder
    RobotMap::shooter_l->SetFeedbackDevice(CANTalon::FeedbackDevice::QuadEncoder);
    //allows SetSetpoint to apply to speed from cimcoder and not from
    RobotMap::shooter_l->SetTalonControlMode(CANTalon::TalonControlMode::kSpeedMode);
    RobotMap::shooter_l->SetSensorDirection(false);
    RobotMap::shooter_l->ConfigNominalOutputVoltage(+0.0f, -0.0f);
    RobotMap::shooter_l->SelectProfileSlot(0);
    RobotMap::shooter_r->SetTalonControlMode(CANTalon::TalonControlMode::kFollowerMode);
    RobotMap::shooter_r->Set(PORTS::CAN::shooter_talon_right);
}

// Called just before this Command runs the first time
void Shoot::Initialize() {
    printf("Shoot init\n");
    RobotMap::shooter_l->Set(-IDLE);
}

// Called repeatedly when this Command is scheduled to run
void Shoot::Execute() {
    if (-Robot::oi->getgunner()->GetY(frc::GenericHID::kLeftHand) > 0.1) {
        RobotMap::shooter_l->Set(OPTIMAL_RPM);
    } else {
        RobotMap::shooter_l->Set(-IDLE);
    }
}

// Make this return true when this Command no longer needs to run execute()
bool Shoot::IsFinished() {
    return false;
}

// Called once after isFinished returns true
void Shoot::End() {
    printf("Info: Shoot ended\n");
    RobotMap::shooter_l->Set(0.0);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void Shoot::Interrupted() {
    printf("Warning: Shoot Interrupted!\n");
    RobotMap::shooter_l->Set(0.0);
}
