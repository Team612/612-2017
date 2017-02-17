#include "TalonTest.h"

TalonTest::TalonTest(float timer, float speed, TalonENUM t) :
                    Command("TalonTest", timer){
    this->speed = speed;
    position = t;
    SetTimeout((double)timer);
    //this->timer = timer;
}

void TalonTest::Initialize() {
    printf("Talon test initialize...\n");
    switch (position) {
    case TalonENUM::SHOOTER:
        chosen = RobotMap::shooter;
        std::cout << "Testing Shooter Talon" << std::endl;
        break;
    case TalonENUM::FL:
        chosen = RobotMap::drive_fl;
        std::cout << "Testing Front Left Talon" << std::endl;
        break;
    case TalonENUM::ML:
        chosen = RobotMap::drive_ml;
        std::cout << "Testing Middle Left Talon" << std::endl;
        break;
    case TalonENUM::RL:
        chosen = RobotMap::drive_rl;
        std::cout << "Testing Rear Left Talon" << std::endl;
        break;
    case TalonENUM::FR:
        chosen = RobotMap::drive_fr;
        std::cout << "Testing Front Right Talon" << std::endl;
        break;
    case TalonENUM::MR:
        chosen = RobotMap::drive_mr;
        std::cout << "Testing Middle Right Talon" << std::endl;
        break;
    case TalonENUM::RR:
        chosen = RobotMap::drive_rr;
        std::cout << "Testing Rear Right Talon" << std::endl;
        break;
    case TalonENUM::CLIMBER:
        chosen = RobotMap::climber;
        std::cout << "Testing Climber Talon" << std::endl;
        break;
    case TalonENUM::INTAKE_L:
        chosen = RobotMap::intake_talon_left;
        std::cout << "Testing Left Intake Talon" << std::endl;
        break;
    case TalonENUM::INTAKE_R:
        chosen = RobotMap::intake_talon_right;
        std::cout << "Testing Right Intake Talon" << std::endl;
        break;
    default:
        chosen = nullptr;
        std::cout<<"ERROR: Unexpected TalonENUM IN TalonTest.cpp";
        break;
    }
    //SetTimeout((double)timer);
}

void TalonTest::Execute() {
    if(chosen != nullptr)
        chosen->Set(speed);

}

bool TalonTest::IsFinished() {
  return IsTimedOut();
}

void TalonTest::End() {
    printf("Info: Test Ended\n");
    chosen->Set(0);
}

void TalonTest::Interrupted() {
    printf("WARNING: Test Interrupted\n");
    chosen->Set(0);
}
