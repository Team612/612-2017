#include "Climber.h"
#include "../Commands/Climber/Climb.h"

Climber::Climber() : Subsystem("Climber") {
    RobotMap::climber->SetTalonControlMode(CANTalon::TalonControlMode::kThrottleMode);
    RobotMap::grabber->Set(0); //reset servo position on start up
}

void Climber::InitDefaultCommand() {
    SetDefaultCommand(new Climb());
}


void Climber::Move(float speed) {
    RobotMap::climber->Set(speed);
}

void Climber::Block() {
    RobotMap::climber->Set(0);
}

void Climber::Grab(double position) {
    RobotMap::grabber->Set(position);
}
