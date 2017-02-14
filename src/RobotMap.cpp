#include "RobotMap.h"
#include "LiveWindow/LiveWindow.h"
#include "Ports.h"

std::shared_ptr<CANTalon> RobotMap::talon_shoot_left;
std::shared_ptr<CANTalon> RobotMap::talon_shoot_right;
std::shared_ptr<CANTalon> RobotMap::drive_fl;
std::shared_ptr<CANTalon> RobotMap::drive_rl;
std::shared_ptr<CANTalon> RobotMap::drive_fr;
std::shared_ptr<CANTalon> RobotMap::drive_rr;
std::shared_ptr<CANTalon> RobotMap::intake_talon_left;
std::shared_ptr<CANTalon> RobotMap::intake_talon_right;
std::shared_ptr<CANTalon> RobotMap::climber_talon_left;
std::shared_ptr<CANTalon> RobotMap::climber_talon_right;
std::shared_ptr<RobotDrive> RobotMap::drive;
std::shared_ptr<Encoder> RobotMap::drivetrainleft_encoder;
std::shared_ptr<Encoder> RobotMap::drivetrainright_encoder;
std::shared_ptr<Encoder> RobotMap::shooter_encoder;

void RobotMap::init() {
    LiveWindow *lw = LiveWindow::GetInstance();

    talon_shoot_left.reset(new CANTalon(PORTS::CAN::left_shoot_talon));
    lw->AddActuator("Shooter", "talon_shoot_left", talon_shoot_left);

    talon_shoot_right.reset(new CANTalon(PORTS::CAN::right_shoot_talon));
    lw->AddActuator("Shoorter", "talon_shoot_right", talon_shoot_right);

    drive_fl.reset(new CANTalon(PORTS::CAN::drive_talonFL));
    lw->AddActuator("Drivetrain", "talon_drive_fl", drive_fl);

    drive_rl.reset(new CANTalon(PORTS::CAN::drive_talonRL));
    lw->AddActuator("Drivetrain", "talon_drive_rl", drive_rl);
    drive_rl->SetInverted(true);

    drive_fr.reset(new CANTalon(PORTS::CAN::drive_talonFR));
    lw->AddActuator("Drivetrain", "talon_drive_fr", drive_fr);

    drive_rr.reset(new CANTalon(PORTS::CAN::drive_talonRR));
    lw->AddActuator("Drivetrain", "talon_drive_rr", drive_rr);

    intake_talon_right.reset(new CANTalon(PORTS::CAN::intake_talon_right));
    lw->AddActuator("Intake", "intake_talon_right", intake_talon_right);

    intake_talon_left.reset(new CANTalon(PORTS::CAN::intake_talon_left));
    lw->AddActuator("Intake", "intake_talon_left", intake_talon_left);

    climber_talon_right.reset(new CANTalon(PORTS::CAN::climber_talon_right));
    lw->AddActuator("Climber", "climber_talon_right", climber_talon_right);

    climber_talon_left.reset(new CANTalon(PORTS::CAN::intake_talon_left));
    lw->AddActuator("Climber", "climber_talon_left", climber_talon_left);

    drive.reset(new RobotDrive(drive_fl, drive_rl,
              drive_fr, drive_rr));
    drive->SetSafetyEnabled(false);

    /*drivetrainleft_encoder.reset(new Encoder(PORTS::DIO::drivetrainleft_encoder00, PORTS::DIO::drivetrainleft_encoder01, false, Encoder::k4X));
    lw->AddSensor("Drivetrain", "left_encoder", drivetrainleft_encoder);
    drivetrainleft_encoder->SetDistancePerPulse(1.0);
    drivetrainleft_encoder->SetPIDSourceType(PIDSourceType::kRate);
    drivetrainright_encoder.reset(new Encoder(PORTS::DIO::drivetrainright_encoder00, PORTS::DIO::drivetrainright_encoder01, false, Encoder::k4X));
    lw->AddSensor("Drivetrain", "right_encoder", drivetrainright_encoder);
    drivetrainright_encoder->SetDistancePerPulse(1.0);
    drivetrainright_encoder->SetPIDSourceType(PIDSourceType::kRate);
    lw->AddSensor("Shooter", "shooter_encoder", shooter_encoder);
    shooter_encoder->SetDistancePerPulse(1.0);
    shooter_encoder->SetPIDSourceType(PIDSourceType::kRate);*/
}
