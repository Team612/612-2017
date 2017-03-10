#include "SetShooter.h"
#include "../../Robot.h"

SetShooter::SetShooter(double speed) : Command("Set Shooter") {
    this->speed = speed;
//    SetTimeout(time);
    Requires(Robot::shooter.get());
}

void SetShooter::Initialize() {

}

void SetShooter::Execute() {
    Robot::shooter->Spin(speed);
}

bool SetShooter::IsFinished() {
    return false;
}

void SetShooter::End() {
    Robot::shooter->Spin(0.0);
}

void SetShooter::Interrupted() {
    std::cout << "Warning: SetShooter interrupted!" << std::endl;
    Robot::shooter->Spin(0.0);
}
