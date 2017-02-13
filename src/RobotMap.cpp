#include "RobotMap.h"
#include "LiveWindow/LiveWindow.h"
#include "Ports.h"

std::shared_ptr<CANTalon> RobotMap::shooter;
std::shared_ptr<CANTalon> RobotMap::drive_fl;
std::shared_ptr<CANTalon> RobotMap::drive_ml;
std::shared_ptr<CANTalon> RobotMap::drive_rl;
std::shared_ptr<CANTalon> RobotMap::drive_fr;
std::shared_ptr<CANTalon> RobotMap::drive_mr;
std::shared_ptr<CANTalon> RobotMap::drive_rr;
std::shared_ptr<CANTalon> RobotMap::intake_talon_left;
std::shared_ptr<CANTalon> RobotMap::intake_talon_right;
std::shared_ptr<CANTalon> RobotMap::climber;
std::shared_ptr<RobotDrive> RobotMap::drive;

void RobotMap::init() {
    LiveWindow *lw = LiveWindow::GetInstance();

    shooter.reset(new CANTalon(PORTS::CAN::shooter));
    lw->AddActuator("Shooter", "shooter", shooter);

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

    climber.reset(new CANTalon(PORTS::CAN::climber));
    lw->AddActuator("Climber", "climber", climber);

    drive.reset(new RobotDrive(drive_fl, drive_rl,
              drive_fr, drive_rr));
    drive->SetSafetyEnabled(false);
}
