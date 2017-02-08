#include "Intake.h"

Intake::Intake() :
    frc::Subsystem("Intake") {

}

void Intake::InitDefaultCommand() {

}

void Intake::IntakeFuel(float speed) {
    RobotMap::intake_talon_left->Set(speed);
    RobotMap::intake_talon_right->Set(speed);
}
