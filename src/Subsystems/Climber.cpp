#include "Climber.h"
#include "../Commands/Climber/Climb.h"
#include "lib612/Networking/Networking.h"

Climber::Climber() : Subsystem("Climber") {
    lib612::Networking::AddFunction([](){
       //frc::SmartDashboard::PutNumber("Climber current", RobotMap::climber_srx->GetOutputCurrent());
    });
}

void Climber::InitDefaultCommand() {
    SetDefaultCommand(new Climb());
}

//Functions left for extendability
void Climber::Move(float speed) {
	RobotMap::climber_srx->Set(speed);
}

void Climber::Block() {
    RobotMap::climber_srx->Set(0);
}
