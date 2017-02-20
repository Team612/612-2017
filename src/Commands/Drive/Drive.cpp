#include "Drive.h"
#include "../../Robot.h"

Drive::Drive(): Command() {
    printf("Drive constructor\n");
    Requires(Robot::drivetrain.get());
}

void Drive::Initialize() {
    printf("Drive init\n");
}

void Drive::Execute() {
    Robot::drivetrain->Throttle(-Robot::oi->getdriver()->GetY(frc::GenericHID::kLeftHand), -Robot::oi->getdriver()->GetY(frc::GenericHID::kRightHand));
    //motor feed safety
    frc::Wait(0.005);
}

bool Drive::IsFinished() {
    return false;
}

void Drive::End() {
    printf("Info: Drive ended!\n");
    Robot::drivetrain->SetVelocity(static_cast<double>(0), static_cast<double>(0));

}

void Drive::Interrupted() {
    printf("ERROR: Drive interrupted!\n");
    Robot::drivetrain->SetVelocity(static_cast<double>(0), static_cast<double>(0));
}
