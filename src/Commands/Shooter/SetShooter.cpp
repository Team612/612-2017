#include "SetShooter.h"
#include "../../Robot.h"

SetShooter::SetShooter(double time, double multiplier) : Command("Set Shooter") {
    this->multiplier = multiplier;
    SetTimeout(time);
    Requires(Robot::shooter.get());
}

void SetShooter::Initialize() {

}

void SetShooter::Execute() {
    Robot::shooter->Spin(OPTIMAL_RPM * multiplier);
}

bool SetShooter::IsFinished() {
    return IsTimedOut();
}

void SetShooter::End() {
    Robot::shooter->Spin(0.0);
}

void SetShooter::Interrupted() {
    std::cout << "Warning: SetShooter interrupted!" << std::endl;
    Robot::shooter->Spin(0.0);
}
