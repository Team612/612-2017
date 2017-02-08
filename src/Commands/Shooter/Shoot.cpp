#include "Shoot.h"
#include "../../Robot.h"

Shoot::Shoot(): Command() {
        // Use requires() here to declare subsystem dependencies
    // eg. requires(Robot::chassis.get());
    printf("Shoot constructor\n");
    Requires(Robot::shooter.get());
    RobotMap::talon_shoot_left->SetPID(0.22, 0, 0, 0.1097);
    //get values from connected cimcoder
    RobotMap::talon_shoot_left->SetFeedbackDevice(CANTalon::FeedbackDevice::QuadEncoder);
    //allows SetSetpoint to apply to speed from cimcoder and not from
    RobotMap::talon_shoot_left->SetControlMode(frc::CANSpeedController::ControlMode::kSpeed);
    RobotMap::talon_shoot_right->SetControlMode(frc::CANSpeedController::ControlMode::kFollower);
    RobotMap::talon_shoot_left->SetSensorDirection(false);
    RobotMap::talon_shoot_left->ConfigNominalOutputVoltage(+0.0f, -0.0f);
    RobotMap::talon_shoot_left->SelectProfileSlot(0);
}

// Called just before this Command runs the first time
void Shoot::Initialize() {
    printf("Shoot init\n");
    RobotMap::talon_shoot_left->Set(-IDLE);
    RobotMap::talon_shoot_right->Set(PORTS::CAN::left_shoot_talon);
}

// Called repeatedly when this Command is scheduled to run
void Shoot::Execute() {
    if (Robot::oi->getgunner()->GetY(frc::GenericHID::kLeftHand) > 0.1) {
        RobotMap::talon_shoot_left->Set(OPTIMAL_RPM);
    } else {
        RobotMap::talon_shoot_left->Set(-IDLE);
    }
    RobotMap::talon_shoot_right->Set(PORTS::CAN::left_shoot_talon);
}

// Make this return true when this Command no longer needs to run execute()
bool Shoot::IsFinished() {
    return false;
}

// Called once after isFinished returns true
void Shoot::End() {
    printf("Info: Shoot ended\n");
    RobotMap::talon_shoot_left->Set(0.0);
    RobotMap::talon_shoot_right->Set(PORTS::CAN::left_shoot_talon);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void Shoot::Interrupted() {
    printf("Warning: Shoot Interrupted!\n");
    RobotMap::talon_shoot_left->Set(0.0);
    RobotMap::talon_shoot_right->Set(PORTS::CAN::left_shoot_talon);
}
