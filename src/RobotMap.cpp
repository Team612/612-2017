#include "RobotMap.h"
#include "LiveWindow/LiveWindow.h"
#include "Ports.h"


std::shared_ptr<CANTalon> RobotMap::shooter_l;
std::shared_ptr<CANTalon> RobotMap::shooter_r;
std::shared_ptr<CANTalon> RobotMap::drive_fl;
std::shared_ptr<CANTalon> RobotMap::drive_ml;
std::shared_ptr<CANTalon> RobotMap::drive_rl;
std::shared_ptr<CANTalon> RobotMap::drive_fr;
std::shared_ptr<CANTalon> RobotMap::drive_mr;
std::shared_ptr<CANTalon> RobotMap::drive_rr;
std::shared_ptr<CANTalon> RobotMap::intake_talon_left;
std::shared_ptr<CANTalon> RobotMap::intake_talon_right;
std::shared_ptr<CANTalon> RobotMap::climber_l;
std::shared_ptr<CANTalon> RobotMap::climber_r;
std::shared_ptr<Servo> RobotMap::grabber;
std::shared_ptr<PowerDistributionPanel> RobotMap::pdp;
std::shared_ptr<RobotDrive> RobotMap::drive;
//std::shared_ptr<RobotDrive> RobotMap::drive;

void RobotMap::init() {
    LiveWindow *lw = LiveWindow::GetInstance();

    shooter_l.reset(new CANTalon(PORTS::CAN::shooter_talon_left));
    lw->AddActuator("Shooter", "shooter_l", shooter_l);

    shooter_r.reset(new CANTalon(PORTS::CAN::shooter_talon_right));
    lw->AddActuator("Shooter", "shooter_r", shooter_r);

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

    climber_l.reset(new CANTalon(PORTS::CAN::climber_talon_left));
    lw->AddActuator("Climber", "climber_l", climber_l);

    climber_r.reset(new CANTalon(PORTS::CAN::climber_talon_right));
    lw->AddActuator("Climber", "climber_r", climber_r);

    pdp.reset(new PowerDistributionPanel(PORTS::CAN::module));

    drive.reset(new RobotDrive(drive_ml.get(), drive_mr.get()));

    grabber.reset(new Servo(PORTS::PWM::servo));
    lw->AddActuator("Climber", "grabber", grabber);

    /*drive.reset(new RobotDrive(drive_fl, drive_rl,
              drive_fr, drive_rr));
    drive->SetSafetyEnabled(false);*/
}
