#include "Climber.h"
#include "../Commands/Climber/Climb.h"

Climber::Climber() : Subsystem("Climber") {
    RobotMap::climber_l->SetTalonControlMode(CANTalon::TalonControlMode::kThrottleMode);
    RobotMap::climber_r->SetTalonControlMode(CANTalon::TalonControlMode::kFollowerMode);
    RobotMap::climber_r->Set(PORTS::CAN::climber_talon_left);
    RobotMap::grabber->Set(0); //reset servo position on start up
}

void Climber::InitDefaultCommand() {
    //SetDefaultCommand(new Climb());
}


void Climber::Climb(float speed) {
    RobotMap::climber_l->Set(speed);
}

void Climber::Block() {
    RobotMap::climber_l->Set(0);
}

void Climber::Grab(double position) {
    RobotMap::grabber->Set(position);
}
