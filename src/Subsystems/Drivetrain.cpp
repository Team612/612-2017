#include "Drivetrain.h"
#include "../RobotMap.h"
#include "../Commands/Drive.h"

Drivetrain::Drivetrain() : Subsystem("Drivetrain") {
    left_encoder = RobotMap::drivetrainright_encoder;
    right_encoder = RobotMap::drivetrainright_encoder;
}

void Drivetrain::InitDefaultCommand() {
    SetDefaultCommand(new Drive());
}
