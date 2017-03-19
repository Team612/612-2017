#include "Drive.h"
#include "../../Robot.h"
#include <cmath>


Drive::Drive(): Command() {
    printf("Drive constructor\n");
    Requires(Robot::drivetrain.get());
}

void Drive::Initialize() {
    printf("Drive init\n");
}

void Drive::Execute() {
    if(!SmartDashboard::GetBoolean("Joe Mode", true)) {
        Robot::drivetrain->HaloDrive(Robot::oi->getdriver()->GetSmoothX(frc::GenericHID::kRightHand) * Robot::drive_limit,
                                     Robot::oi->getdriver()->GetSmoothY(frc::GenericHID::kLeftHand) * -Robot::drive_limit,
                                     Robot::oi->getdriver()->GetBumper(frc::GenericHID::kLeftHand));
    } else {
        Robot::drivetrain->TankDrive(Robot::oi->getdriver()->GetSmoothY(frc::GenericHID::kLeftHand) * Robot::drive_limit,
                                     Robot::oi->getdriver()->GetSmoothY(frc::GenericHID::kRightHand) * Robot::drive_limit);
    }
    //motor feed safety
    frc::Wait(0.005);
}

bool Drive::IsFinished() {
    return false;
}

void Drive::End() {
    printf("Info: Drive ended!\n");
    Robot::drivetrain->TankDrive(0, 0);
}

void Drive::Interrupted() {
    printf("Warning: Drive interrupted!\n");
    Robot::drivetrain->TankDrive(0, 0);
}
