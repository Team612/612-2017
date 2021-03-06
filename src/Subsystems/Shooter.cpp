#include "Shooter.h"
#include "../RobotMap.h"
#include "../Commands/Shooter/Shoot.h"
#include "lib612/Networking/Networking.h"

Shooter::Shooter() : Subsystem("Shooter") {
    RobotMap::shooter_l->SetFeedbackDevice(CANTalon::FeedbackDevice::CtreMagEncoder_Relative);
    RobotMap::shooter_l->SetTalonControlMode(CANTalon::TalonControlMode::kSpeedMode);
    RobotMap::shooter_l->SetSensorDirection(false);

    RobotMap::shooter_l->ConfigNominalOutputVoltage(+0.0f, -0.0f);
    RobotMap::shooter_l->ConfigPeakOutputVoltage(0, -12.0);

    RobotMap::shooter_l->SelectProfileSlot(0);
    RobotMap::shooter_l->SetPID(0.2, 0.001, 0.0, 0.025);
    RobotMap::shooter_l->SetIzone(2000);

    lib612::Networking::AddFunction([](){
        frc::SmartDashboard::PutNumber("Shooter speed", RobotMap::shooter_l->GetSpeed());
        frc::SmartDashboard::PutNumber("Shooter I Error", RobotMap::shooter_l->GetIaccum());
        //frc::SmartDashboard::PutNumber("I Zone", RobotMap::shooter_l->GetIzone());
        frc::SmartDashboard::PutNumber("Shooter Error", RobotMap::shooter_l->GetClosedLoopError());
        frc::SmartDashboard::PutNumber("Shooter voltage", RobotMap::shooter_l->GetOutputVoltage());
        //frc::SmartDashboard::PutNumber("Shooter current", RobotMap::shooter_l->GetOutputCurrent());
    });
}

void Shooter::InitDefaultCommand() {
    SetDefaultCommand(new Shoot());
}

void Shooter::Spin(float speed) {
    RobotMap::shooter_l->SetSetpoint(speed);
    //RobotMap::shooter_l->SetIzone((unsigned)frc::SmartDashboard::GetNumber("Shooter I Zone", 0));
    //RobotMap::shooter_r->Set(RobotMap::shooter_l->GetDeviceID());
    //RobotMap::shooter_r->Set(PORTS::CAN::shooter_talon_left);
}

void Shooter::Agitate() {
    RobotMap::agitator->Set(0.2f);
}
