#include "RobotMap.h"
#include "LiveWindow/LiveWindow.h"
#include "Ports.h"

std::shared_ptr<CANTalon> RobotMap::talon_shoot;
std::shared_ptr<CANTalon> RobotMap::drive_fl;
std::shared_ptr<CANTalon> RobotMap::drive_rl;
std::shared_ptr<CANTalon> RobotMap::drive_fr;
std::shared_ptr<CANTalon> RobotMap::drive_rr;
std::shared_ptr<CANTalon> RobotMap::conveyor_talon;
std::shared_ptr<CANTalon> RobotMap::climber_talon;
std::shared_ptr<CANTalon> RobotMap::intake_talon;
std::shared_ptr<RobotDrive> RobotMap::drive;
std::shared_ptr<Encoder> RobotMap::drivetrainleft_encoder;
std::shared_ptr<Encoder> RobotMap::drivetrainright_encoder;

void RobotMap::init() {
    LiveWindow *lw = LiveWindow::GetInstance();

    talon_shoot.reset(new CANTalon(PORTS::CAN::shoot_talon00));
    lw->AddActuator("Shooter", "talon_shoot", talon_shoot);

    drive_fl.reset(new CANTalon(PORTS::CAN::drive_talonFL));
    lw->AddActuator("Drivetrain", "talon_drive_fl", drive_fl);

    drive_rl.reset(new CANTalon(PORTS::CAN::drive_talonRL));
    lw->AddActuator("Drivetrain", "talon_drive_rl", drive_rl);
    drive_rl->SetInverted(true);

    drive_fr.reset(new CANTalon(PORTS::CAN::drive_talonFR));
    lw->AddActuator("Drivetrain", "talon_drive_fr", drive_fr);

    drive_rr.reset(new CANTalon(PORTS::CAN::drive_talonRR));
    lw->AddActuator("Drivetrain", "talon_drive_rr", drive_rr);

    conveyor_talon.reset(new CANTalon(PORTS::CAN::conveyor_talon));
    lw->AddActuator("Conveyor", "conveyor_talon", conveyor_talon);

    climber_talon.reset(new CANTalon(PORTS::CAN::climber_talon));
    lw->AddActuator("Climber", "conveyor_talon", climber_talon);

    intake_talon.reset(new CANTalon(PORTS::CAN::intake_talon));
    lw->AddActuator("Intake", "intake_talon", intake_talon);

    drive.reset(new RobotDrive(drive_fl, drive_rl,
              drive_fr, drive_rr));
    drive->SetSafetyEnabled(false);

    drivetrainleft_encoder.reset(new Encoder(PORTS::DIO::drivetrainleft_encoder00, PORTS::DIO::drivetrainleft_encoder01, false, Encoder::k4X));
    lw->AddSensor("Drivetrain", "left_encoder", drivetrainleft_encoder);
    drivetrainleft_encoder->SetDistancePerPulse(1.0);
    drivetrainleft_encoder->SetPIDSourceType(PIDSourceType::kRate);
    drivetrainright_encoder.reset(new Encoder(PORTS::DIO::drivetrainright_encoder00, PORTS::DIO::drivetrainright_encoder01, false, Encoder::k4X));
    lw->AddSensor("Drivetrain", "right_encoder", drivetrainright_encoder);
    drivetrainright_encoder->SetDistancePerPulse(1.0);
    drivetrainright_encoder->SetPIDSourceType(PIDSourceType::kRate);
}
