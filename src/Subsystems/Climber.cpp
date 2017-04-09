#include "Climber.h"
#include "../Commands/Climber/Climb.h"
#include "lib612/Networking/Networking.h"

Climber::Climber() : Subsystem("Climber") {
    RobotMap::climber_l->SetTalonControlMode(CANTalon::TalonControlMode::kThrottleMode);
    RobotMap::climber_l->SetCurrentLimit(40);
    RobotMap::climber_l->EnableCurrentLimit(true);

    RobotMap::climber_r->SetTalonControlMode(CANTalon::TalonControlMode::kThrottleMode);
    //RobotMap::climber_r->SetClosedLoopOutputDirection(true);
    RobotMap::climber_r->SetCurrentLimit(40);
    RobotMap::climber_r->EnableCurrentLimit(true);
    //RobotMap::climber_r->Set(RobotMap::climber_r->GetDeviceID());

    lib612::Networking::AddFunction([](){
       //frc::SmartDashboard::PutNumber("Climber current", RobotMap::climber_srx->GetOutputCurrent());
        frc::SmartDashboard::PutNumber("Total Climber Current", RobotMap::climber_r->GetOutputCurrent() * 1000 +
                                                                RobotMap::climber_l->GetOutputCurrent() * 1000);
    });
}

void Climber::InitDefaultCommand() {
    SetDefaultCommand(new Climb());
}

//Functions left for extendability
void Climber::Move(float speed) {
	RobotMap::climber_l->Set(speed);
    //RobotMap::climber_srx->Set(speed);
    RobotMap::climber_r->Set(RobotMap::climber_l->GetDeviceID());
}

void Climber::Block() {
    RobotMap::climber_l->Set(0);
    //RobotMap::climber_srx->Set(0);
    RobotMap::climber_r->Set(0);
}
