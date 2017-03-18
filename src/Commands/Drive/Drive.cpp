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
    //exists to facilitate smoothing function testing
    //std::cout << "Drive.cpp: " << "Throttle: " << Robot::oi->getdriver()->GetSmoothY(frc::GenericHID::kLeftHand) << " Wheel: " << Robot::oi->getdriver()->GetSmoothX(frc::GenericHID::kRightHand) << std::endl;

    if(!SmartDashboard::GetBoolean("Joe Mode", true)) {
        Robot::drivetrain->HaloDrive(Robot::oi->getdriver()->GetSmoothX(frc::GenericHID::kRightHand),
                                     Robot::oi->getdriver()->GetSmoothY(frc::GenericHID::kLeftHand),
                                     Robot::oi->getdriver()->GetBumper(frc::GenericHID::kLeftHand));
    } else {
        Robot::drivetrain->TankDrive(Robot::oi->getdriver()->GetSmoothY(frc::GenericHID::kLeftHand),
                                     Robot::oi->getdriver()->GetSmoothY(frc::GenericHID::kRightHand));
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
    printf("ERROR: Drive interrupted!\n");
    Robot::drivetrain->TankDrive(0, 0);
}
