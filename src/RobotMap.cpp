#include "RobotMap.h"
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
std::shared_ptr<TalonSRX> RobotMap::climber_srx;
std::shared_ptr<CANTalon> RobotMap::agitator;
std::shared_ptr<PowerDistributionPanel> RobotMap::pdp;
std::shared_ptr<DoubleSolenoid> RobotMap::shifter;
std::shared_ptr<RobotDrive> RobotMap::drive;
//std::shared_ptr<Ultrasonic> RobotMap::ultrasonic;
std::shared_ptr<lib612::AnalogUltrasonic> RobotMap::new_ultrasonic;
std::shared_ptr<Compressor> RobotMap::compressor;

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

    agitator.reset(new CANTalon(PORTS::CAN::agitator));

    pdp.reset(new PowerDistributionPanel(PORTS::CAN::module));

    //drive.reset(new RobotDrive(drive_ml.get(), drive_mr.get()));
                                                                                                
    //ultrasonic.reset(new Ultrasonic(static_cast<int>(PORTS::DIO::ultrasonic_in), static_cast<int>(PORTS::DIO::ultrasonic_in), frc::Ultrasonic::DistanceUnit::kMilliMeters)); //tfw C++

    new_ultrasonic.reset(new lib612::AnalogUltrasonic(PORTS::PWM::analog_ultrasonic));

    shifter.reset(new DoubleSolenoid(0, 1));
    lw->AddActuator("Shifter", "shifter", shifter);
    shifter->Set(DoubleSolenoid::Value::kForward);
  
    compressor.reset(new Compressor(PORTS::PCM::compressor));
    compressor->Start();

    /*drive.reset(new RobotDrive(drive_fl, drive_rl,
     drive_fr, drive_rr));
    drive->SetSafetyEnabled(false);*/

    climber_srx.reset(new TalonSRX(PORTS::PWM::climber));
    lw->AddActuator("Climber", "climber_srx", climber_srx);
}
