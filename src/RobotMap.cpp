#include "RobotMap.h"
#include "LiveWindow/LiveWindow.h"
#include "Ports.h"

std::shared_ptr<CANTalon> RobotMap::shoot_l;
std::shared_ptr<CANTalon> RobotMap::shoot_r;
std::shared_ptr<CANTalon> RobotMap::drive_fl;
std::shared_ptr<CANTalon> RobotMap::drive_ml;
std::shared_ptr<CANTalon> RobotMap::drive_rl;
std::shared_ptr<CANTalon> RobotMap::drive_fr;
std::shared_ptr<CANTalon> RobotMap::drive_mr;
std::shared_ptr<CANTalon> RobotMap::drive_rr;
std::shared_ptr<CANTalon> RobotMap::intake_talon_left;
std::shared_ptr<CANTalon> RobotMap::intake_talon_right;
std::shared_ptr<CANTalon> RobotMap::climber_l;
//std::shared_ptr<RobotDrive> RobotMap::drive;

void RobotMap::init() {
    LiveWindow *lw = LiveWindow::GetInstance();

    shoot_l.reset(new CANTalon(PORTS::CAN::shoot_l));
    lw->AddActuator("Shooter", "shooter_l", shoot_l);

    shoot_r.reset(new CANTalon(PORTS::CAN::shoot_r));
    lw->AddActuator("Shooter", "shooter_r", shoot_r);

    drive_ml.reset(new CANTalon(PORTS::CAN::drive_talonML));
    lw->AddActuator("Drivetrain", "talon_drive_ml", drive_ml);

    drive_fl.reset(new CANTalon(PORTS::CAN::drive_talonFL));
    lw->AddActuator("Drivetrain", "talon_drive_fl", drive_fl);

    drive_rl.reset(new CANTalon(PORTS::CAN::drive_talonRL));
    lw->AddActuator("Drivetrain", "talon_drive_rl", drive_rl);
    //drive_rl->SetInverted(true);

    drive_mr.reset(new CANTalon(PORTS::CAN::drive_talonMR));
    lw->AddActuator("Drivetrain", "talon_drive_mr", drive_mr);

    drive_fr.reset(new CANTalon(PORTS::CAN::drive_talonFR));
    lw->AddActuator("Drivetrain", "talon_drive_fr", drive_fr);

    drive_rr.reset(new CANTalon(PORTS::CAN::drive_talonRR));
    lw->AddActuator("Drivetrain", "talon_drive_rr", drive_rr);

    intake_talon_right.reset(new CANTalon(PORTS::CAN::intake_talon_right));
    lw->AddActuator("Intake", "intake_talon_right", intake_talon_right);

    intake_talon_left.reset(new CANTalon(PORTS::CAN::intake_talon_left));
    lw->AddActuator("Intake", "intake_talon_left", intake_talon_left);

    climber_l.reset(new CANTalon(PORTS::CAN::climber_l));
    lw->AddActuator("Climber", "climber_l", climber_l);

    /*drive.reset(new RobotDrive(drive_fl, drive_rl,
              drive_fr, drive_rr));
    drive->SetSafetyEnabled(false);*/
}
