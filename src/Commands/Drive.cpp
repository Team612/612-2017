


#include "Drive.h"
#include "../Robot.h"


Drive::Drive(): Command() {

}



void Drive::Initialize() {

}


void Drive::Execute() {
  RobotMap::drive->TankDrive(-Robot::oi->getdriver()->GetY(frc::GenericHID::kLeftHand),-Robot::oi->getdriver()->GetY(frc::GenericHID::kRightHand));
}


bool Drive::IsFinished() {
    return false;
}


void Drive::End() {

}


void Drive::Interrupted() {

}
