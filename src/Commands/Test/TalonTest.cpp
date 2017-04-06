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
    case TalonENUM::SHOOTER_L:
        chosen = RobotMap::shooter_l;
        std::cout << "Testing Shooter Talon (Left)" << std::endl;
        break;
    case TalonENUM::SHOOTER_R:
        chosen = RobotMap::shooter_r;
        std::cout << "Testing Shooter Talon (Right)" << std::endl;
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
        chosen = RobotMap::climber_l;
        std::cout << "Testing Climber Talon (Left)" << std::endl;
        break;
    /*case TalonENUM::CLIMBER:
        chosenSRX = nullptr;
        std::cout << "Warning: Climber testing is disabled" << std::endl;
        break;*/
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
    OriginalControlMode = chosen->GetTalonControlMode();
    chosen->SetTalonControlMode(CANTalon::TalonControlMode::kThrottleMode);
    //SetTimeout((double)timer);
}

void TalonTest::Execute() {
    if(chosen != nullptr) {
        chosen->Set(speed);
        if(OriginalControlMode == CANTalon::TalonControlMode::kSpeedMode)
            std::cout << "Encoder test: " << chosen->GetAnalogIn() << std::endl;
    }
    if(chosenSRX != nullptr) {
        chosenSRX->Set(speed);
        std::cout << "Encoder test: " << chosenSRX->Get()<< std::endl;
    }
}

bool TalonTest::IsFinished() {
  return IsTimedOut();
}

void TalonTest::End() {
    printf("Info: Test Ended\n");
    chosen->SetTalonControlMode(OriginalControlMode);
    chosen->Set(0);
}

void TalonTest::Interrupted() {
    printf("WARNING: Test Interrupted\n");
    chosen->SetTalonControlMode(OriginalControlMode);
    chosen->Set(0);
}
