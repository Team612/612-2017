#include "Shoot.h"
#include "../../Robot.h"

Shoot::Shoot(): Command() {
        // Use requires() here to declare subsystem dependencies
    // eg. requires(Robot::chassis.get());
    Requires(Robot::shooter.get());
    RobotMap::talon_shoot->SetPID(0.22, 0, 0, 0.1097);
    //get values from connected cimcoder
    RobotMap::talon_shoot->SetFeedbackDevice(CANTalon::FeedbackDevice::QuadEncoder);
    //allows SetSetpoint to apply to speed from cimcoder and not from
    RobotMap::talon_shoot->SetControlMode(frc::CANSpeedController::ControlMode::kSpeed);
    RobotMap::talon_shoot->SetSensorDirection(false);
    RobotMap::talon_shoot->ConfigNominalOutputVoltage(+0.0f, -0.0f);
    RobotMap::talon_shoot->SelectProfileSlot(0);
}

// Called just before this Command runs the first time
void Shoot::Initialize() {
    RobotMap::talon_shoot->Set(-IDLE);
}

// Called repeatedly when this Command is scheduled to run
void Shoot::Execute() {
    if (Robot::oi->getgunner()->GetY(frc::GenericHID::kLeftHand) > 0.1) {
        RobotMap::talon_shoot->Set(OPTIMAL_RPM);
    } else {
        RobotMap::talon_shoot->Set(IDLE);
    }
}

// Make this return true when this Command no longer needs to run execute()
bool Shoot::IsFinished() {
    return false;
}

// Called once after isFinished returns true
void Shoot::End() {
    RobotMap::talon_shoot->Set(0.0);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void Shoot::Interrupted() {
    RobotMap::talon_shoot->Set(0.0);
}
