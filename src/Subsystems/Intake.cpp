#include "Intake.h"

Intake::Intake() :
    frc::Subsystem("Intake") {

}

void Intake::InitDefaultCommand() {

}

void Intake::IntakeFuel(float speed) {
    //RobotMap::intake_talon->Set(speed);
}
