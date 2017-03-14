#include "Drive.h"
#include "../../Robot.h"
#include <cmath>

#define JOE
/*! \brief Allows the driver to control the robot's drivetrain using the left and right sticks with a smoothed tank drive. */
/*! Constructor for Drive. */
Drive::Drive(): Command() {
    printf("Drive constructor\n");
    Requires(Robot::drivetrain.get());
}
/*! Intializes Drive. No fuction other than a printout notification. */
void Drive::Initialize() {
    printf("Drive init\n");
}
/*! Takes joystick input and uses it to drive the drivetrain via HaloDrive or TankDrive, after dampening it to 60% power. */
void Drive::Execute() {
    //exists to facilitate smoothing function testing
    //std::cout << "Drive.cpp: " << "Throttle: " << Robot::oi->getdriver()->GetSmoothY(frc::GenericHID::kLeftHand) << " Wheel: " << Robot::oi->getdriver()->GetSmoothX(frc::GenericHID::kRightHand) << std::endl;
#ifndef JOE
    Robot::drivetrain->HaloDrive(Robot::oi->getdriver()->GetSmoothX(frc::GenericHID::kRightHand) * 0.6,
            Robot::oi->getdriver()->GetSmoothY(frc::GenericHID::kLeftHand) * 0.6,
            true);
#else
    Robot::drivetrain->TankDrive(Robot::oi->getdriver()->GetSmoothY(frc::GenericHID::kLeftHand) * -0.6,
                                 Robot::oi->getdriver()->GetSmoothY(frc::GenericHID::kRightHand) * -0.6);
#endif
    //motor feed safety
    frc::Wait(0.005);
}
/*! Returns false. */
bool Drive::IsFinished() {
    return false;
}
/*! Sets the drivetrain to stop. */
void Drive::End() {
    printf("Info: Drive ended!\n");
    Robot::drivetrain->TankDrive(0, 0);
}
/*! Sets the drivetrain to stop. */
void Drive::Interrupted() {
    printf("ERROR: Drive interrupted!\n");
    Robot::drivetrain->TankDrive(0, 0);
}
