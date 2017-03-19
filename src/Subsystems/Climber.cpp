#include "Climber.h"
#include "../Commands/Climber/Climb.h"
#include "lib612/Networking/Networking.h"

Climber::Climber() : Subsystem("Climber") {
//    RobotMap::climber_l->SetTalonControlMode(CANTalon::TalonControlMode::kThrottleMode);
//    RobotMap::climber_r->SetTalonControlMode(CANTalon::TalonControlMode::kFollowerMode);
//    RobotMap::climber_r->Set(RobotMap::climber_l->GetDeviceID());
    RobotMap::grabber->Set(0); //reset servo position on start up
    lib612::Networking::AddFunction([](){
       frc::SmartDashboard::PutNumber("Climber current", RobotMap::climber_l->GetOutputCurrent());
    });
}

void Climber::InitDefaultCommand() {
    SetDefaultCommand(new Climb());
}

//Functions left for extendability
void Climber::Move(float speed) {
//    RobotMap::climber_l->Set(speed);
	RobotMap::climber_spark->Set(speed);
}

void Climber::Block() {
    RobotMap::climber_spark->Set(0);
}

void Climber::Grab(double position) {
    RobotMap::grabber->Set(position);
}
