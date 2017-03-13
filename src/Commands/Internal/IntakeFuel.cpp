#include "IntakeFuel.h"

IntakeFuel::IntakeFuel() {
    Requires(Robot::intake.get());
}

void IntakeFuel::Initialize() {

}

void IntakeFuel::Execute() {
    //Drive team liked this when it was on soda
    if(Robot::oi->getgunner()->GetSmoothTrigger(frc::GenericHID::kRightHand) > 0.01) {
        if(Robot::oi->getgunner()->GetBumper(frc::GenericHID::kLeftHand))
            Robot::intake->ClearBalls();
        else
            Robot::intake->IntakeFuel();
    } else {
        Robot::intake->Stop();
    }

    if (RobotMap::intake_talon_left->GetOutputVoltage() > STALL_OUTPUT_THRESHOLD ||
       (RobotMap::intake_talon_left->GetSetpoint() != 0 && RobotMap::intake_talon_left->GetOutputVoltage() < 0.1))
       Robot::oi->getgunner()->SetRumble(GenericHID::kLeftRumble, 1.0);
    else Robot::oi->getgunner()->SetRumble(GenericHID::kLeftRumble, 0.0);

    if (RobotMap::intake_talon_right->GetOutputVoltage() > STALL_OUTPUT_THRESHOLD ||
       (RobotMap::intake_talon_right->GetSetpoint() != 0 && RobotMap::intake_talon_right->GetOutputVoltage() < 0.1))
       Robot::oi->getgunner()->SetRumble(GenericHID::kRightRumble, 1.0);
    else Robot::oi->getgunner()->SetRumble(GenericHID::kRightRumble, 0.0);

}

bool IntakeFuel::IsFinished() {
    return false;
}

void IntakeFuel::End() {
    Robot::intake->Stop();
}

void IntakeFuel::Interrupted() {
    Robot::intake->Stop();
}
