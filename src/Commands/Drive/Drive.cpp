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
    if(abs(Robot::oi->getdriver()->GetY(frc::GenericHID::JoystickHand::kLeftHand)) > 0.1 || abs(Robot::oi->getdriver()->GetY(frc::GenericHID::JoystickHand::kRightHand)) > 0.1)
        Robot::drivetrain->TeleOpDrive(-Robot::oi->getdriver()->GetY(frc::GenericHID::JoystickHand::kLeftHand), -Robot::oi->getdriver()->GetY(frc::GenericHID::JoystickHand::kRightHand));
    //motor feed safety
    frc::Wait(0.005);
}

bool Drive::IsFinished() {
    return false;
}

void Drive::End() {
    printf("Info: Drive ended!\n");
    Robot::drivetrain->TeleOpDrive(0, 0);

}

void Drive::Interrupted() {
    printf("ERROR: Drive interrupted!\n");
    Robot::drivetrain->TeleOpDrive(0, 0);
}
