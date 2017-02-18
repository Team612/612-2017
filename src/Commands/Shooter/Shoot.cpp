#include "Shoot.h"
#include "../../Robot.h"

Shoot::Shoot(): Command() {
        // Use requires() here to declare subsystem dependencies
    // eg. requires(Robot::chassis.get());
    printf("Shoot constructor\n");
    Requires(Robot::shoot_l.get());
    RobotMap::shoot_l->SetPID(0.22, 0, 0, 0.1097);
    //get values from connected cimcoder
    RobotMap::shoot_l->SetFeedbackDevice(CANTalon::FeedbackDevice::QuadEncoder);
    //allows SetSetpoint to apply to speed from cimcoder and not from
    RobotMap::shoot_l->SetControlMode(frc::CANSpeedController::ControlMode::kSpeed);
    RobotMap::shoot_l->SetSensorDirection(false);
    RobotMap::shoot_l->ConfigNominalOutputVoltage(+0.0f, -0.0f);
    RobotMap::shoot_l->SelectProfileSlot(0);
}

// Called just before this Command runs the first time
void Shoot::Initialize() {
    printf("Shoot init\n");
    RobotMap::shoot_l->Set(-IDLE);
}

// Called repeatedly when this Command is scheduled to run
void Shoot::Execute() {
    if (Robot::oi->getgunner()->GetY(frc::GenericHID::kLeftHand) > 0.1) {
        RobotMap::shoot_l->Set(OPTIMAL_RPM);
    } else {
        RobotMap::shoot_l->Set(-IDLE);
    }
}

// Make this return true when this Command no longer needs to run execute()
bool Shoot::IsFinished() {
    return false;
}

// Called once after isFinished returns true
void Shoot::End() {
    printf("Info: Shoot ended\n");
    RobotMap::shooter->Set(0.0);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void Shoot::Interrupted() {
    printf("Warning: Shoot Interrupted!\n");
    RobotMap::shooter->Set(0.0);
}
