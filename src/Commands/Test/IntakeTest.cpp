#include "IntakeTest.h"
#include "../../RobotMap.h"
#include "../../Robot.h"
IntakeTest::IntakeTest() {

}

void IntakeTest::Initialize() {

}

void IntakeTest::Execute() {
  //CHANGE THE CHANNELS FOR THE GetCurrent METHODS TO THE REAL CHANNLES ONES
    if(RobotMap::pdp->GetCurrent(1) >= 35){
        std::cout << "THE INTAKE MOTOR IS DRAWING WAY TO MUCH POWER // LEFT INTAKE MOTOR"<< std::endl;
        Robot::oi->getgunner()->SetRumble(frc::GenericHID::kRightRumble,1);
        Robot::oi->getgunner()->SetRumble(frc::GenericHID::kLeftRumble,1);
    }
    if(!(RobotMap::intake_talon_left->GetSetpoint() == 0) && RobotMap::pdp->GetCurrent(1) == 0 ){
        std::cout <<"THE LEFT INTAKE MOTOR IS AT 0 AMPS AND THE SET POINT IS NOT 0 ";
        Robot::oi->getgunner()->SetRumble(frc::GenericHID::kRightRumble,1);
        Robot::oi->getgunner()->SetRumble(frc::GenericHID::kLeftRumble,1);
      }
    if(RobotMap::pdp->GetCurrent(2) >= 35){
        std::cout << "THE INTAKE MOTOR IS DRAWING WAY TO MUCH POWER // RIGHT INTAKE MOTOR" << std::endl;
        Robot::oi->getgunner()->SetRumble(frc::GenericHID::kRightRumble,1);
        Robot::oi->getgunner()->SetRumble(frc::GenericHID::kLeftRumble,1);
    }
    if(!(RobotMap::intake_talon_right->GetSetpoint() == 0) && RobotMap::pdp->GetCurrent(2) == 0  ){
        std::cout <<"THE RIGHT INTAKE MOTOR IS AT 0 AMPS AND THE SET POINT IS NOT 0 ";
        Robot::oi->getgunner()->SetRumble(frc::GenericHID::kRightRumble,1);
        Robot::oi->getgunner()->SetRumble(frc::GenericHID::kLeftRumble,1);
    }
}

bool IntakeTest::IsFinished() {
    return false;
}

void IntakeTest::End() {

}

void IntakeTest::Interrupted() {

}
