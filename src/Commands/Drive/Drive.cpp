#include <chrono>

#include "Drive.h"
#include "../../Robot.h"
#include "../../RobotMap.h"

Drive::Drive(): Command() {
    printf("Drive constructor\n");
}

void Drive::Initialize() {
    printf("Drive init\n");
    Requires(Robot::drivetrain.get());
}

void Drive::Execute() {
    RobotMap::drive->TankDrive(-Robot::oi->getdriver()->GetY(frc::GenericHID::kLeftHand), -Robot::oi->getdriver()->GetY(frc::GenericHID::kRightHand));

    //Print out joysticks
    /*std::string print = "Left: ";
    print.append(std::to_string(Robot::oi->getdriver()->GetY(frc::GenericHID::kLeftHand)));
    print.append(" Right: ");
    print.append(std::to_string(Robot::oi->getdriver()->GetY(frc::GenericHID::kRightHand)));
    std::printf(print.c_str());*/
    std::this_thread::sleep_for(std::chrono::milliseconds(5));
}

bool Drive::IsFinished() {
    return false;
}

void Drive::End() {
    printf("Info: Drive ended!\n");
    RobotMap::drive->TankDrive(static_cast<double>(0), static_cast<double>(0));

}

void Drive::Interrupted() {
    printf("ERROR: Drive interrupted!\n");
    RobotMap::drive->TankDrive(static_cast<double>(0), static_cast<double>(0));
}
