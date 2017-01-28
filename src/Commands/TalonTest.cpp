#include "TalonTest.h"

TalonTest::TalonTest(float timer, float speed, TalonENUM t) {
  numSpeed = speed;
  position = t;
  SetTimeout((double)timer);

}

void TalonTest::Initialize() {
  switch (position) {
    case TalonENUM::SHOOTER:
      RobotMap::talon_shoot->Set(numSpeed);
      std::cout<< RobotMap::talon_shoot->Get();
      break;
    case TalonENUM::FL:
      RobotMap::drive_fl->Set(numSpeed);
      std::cout<<  RobotMap::drive_fl->Get();
      break;
    case TalonENUM::RL:
      RobotMap::drive_rl->Set(numSpeed);
      std::cout<<  RobotMap::drive_rl->Get();
      break;
    case TalonENUM::FR:
      RobotMap::drive_fr->Set(numSpeed);
      std::cout<<RobotMap::drive_fr->Get();
      break;
    case TalonENUM::RR:
      RobotMap::drive_rr->Set(numSpeed);
      std::cout<<RobotMap::drive_rr->Get();
      break;
    default:
      std::cout<<"ERROR IN TALON TalonTest.cpp";
      break;

  }
}

void TalonTest::Execute() {


}

bool TalonTest::IsFinished() {
  return IsTimedOut();
}

void TalonTest::End() {

}

void TalonTest::Interrupted() {

}
