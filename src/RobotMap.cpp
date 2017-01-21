#include "RobotMap.h"
#include "LiveWindow/LiveWindow.h"
#include "Ports.h"

std::shared_ptr<SpeedController> RobotMap::talon_shoot;
std::shared_ptr<SpeedController> RobotMap::drive_fl;
std::shared_ptr<SpeedController> RobotMap::drive_rl;
std::shared_ptr<SpeedController> RobotMap::drive_fr;
std::shared_ptr<SpeedController> RobotMap::drive_rr;
std::shared_ptr<RobotDrive> RobotMap::drive;
std::shared_ptr<Encoder> RobotMap::drivetrainleft_encoder;
std::shared_ptr<Encoder> RobotMap::drivetrainright_encoder;

void RobotMap::init() {
    LiveWindow *lw = LiveWindow::GetInstance();

    talon_shoot.reset(new TalonSRX(PORTS::CAN::shoot_talon00));
    lw->AddActuator("Shooter", "talon_shoot", std::static_pointer_cast<TalonSRX>(talon_shoot));

    drive_fl.reset(new Talon(PORTS::CAN::drive_talon01));
    lw->AddActuator("Drivetrain", "talon_drive_fl", std::static_pointer_cast<Talon>(drive_fl));

    drive_rl.reset(new Talon(PORTS::CAN::drive_talon02));
    lw->AddActuator("Drivetrain", "talon_drive_rl", std::static_pointer_cast<Talon>(drive_rl));

    drive_fr.reset(new Talon(PORTS::CAN::drive_talon03));
    lw->AddActuator("Drivetrain", "talon_drive_fr", std::static_pointer_cast<Talon>(drive_fr));

    drive_rr.reset(new Talon(PORTS::CAN::drive_talon04));
    lw->AddActuator("Drivetrain", "talon_drive_rr", std::static_pointer_cast<Talon>(drive_rr));

    drive.reset(new RobotDrive(drive_fl, drive_rl,
              drive_fr, drive_rr));

    drivetrainleft_encoder.reset(new Encoder(PORTS::DIO::drivetrainleft_encoder00, PORTS::DIO::drivetrainleft_encoder01, false, Encoder::k4X));
    lw->AddSensor("Drivetrain", "left_encoder", drivetrainleft_encoder);
    drivetrainleft_encoder->SetDistancePerPulse(1.0);
    drivetrainleft_encoder->SetPIDSourceType(PIDSourceType::kRate);
    drivetrainright_encoder.reset(new Encoder(PORTS::DIO::drivetrainright_encoder00, PORTS::DIO::drivetrainright_encoder01, false, Encoder::k4X));
    lw->AddSensor("Drivetrain", "right_encoder", drivetrainright_encoder);
    drivetrainright_encoder->SetDistancePerPulse(1.0);
    drivetrainright_encoder->SetPIDSourceType(PIDSourceType::kRate);
}
