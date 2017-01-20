// RobotBuilder Version: 2.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.


// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES
#include "RobotMap.h"
#include "LiveWindow/LiveWindow.h"

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=ALLOCATION
std::shared_ptr<SpeedController> RobotMap::talon_shoot;
std::shared_ptr<SpeedController> RobotMap::drive_fl;
std::shared_ptr<SpeedController> RobotMap::drive_rl;
std::shared_ptr<SpeedController> RobotMap::drive_fr;
std::shared_ptr<SpeedController> RobotMap::drive_rr;
std::shared_ptr<RobotDrive> RobotMap::drive;
std::shared_ptr<Encoder> RobotMap::drivetrainleft_encoder;
std::shared_ptr<Encoder> RobotMap::drivetrainright_encoder;

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=ALLOCATION

void RobotMap::init() {
    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTORS
    LiveWindow *lw = LiveWindow::GetInstance();

    talon_shoot.reset(new TalonSRX(0));
    lw->AddActuator("Shooter", "talon_shoot", std::static_pointer_cast<TalonSRX>(talon_shoot));

    drive_fl.reset(new Talon(4));
    lw->AddActuator("Drivetrain", "talon_drive_fl", std::static_pointer_cast<Talon>(drive_fl));

    drive_rl.reset(new Talon(1));
    lw->AddActuator("Drivetrain", "talon_drive_rl", std::static_pointer_cast<Talon>(drive_rl));

    drive_fr.reset(new Talon(2));
    lw->AddActuator("Drivetrain", "talon_drive_fr", std::static_pointer_cast<Talon>(drive_fr));

    drive_rr.reset(new Talon(3));
    lw->AddActuator("Drivetrain", "talon_drive_rr", std::static_pointer_cast<Talon>(drive_rr));

    drive.reset(new RobotDrive(drive_fl, drive_rl,
              drive_fr, drive_rr));

    drive->SetSafetyEnabled(true);
        drive->SetExpiration(0.1);
        drive->SetSensitivity(0.5);
        drive->SetMaxOutput(1.0);

    drivetrainleft_encoder.reset(new Encoder(0, 1, false, Encoder::k4X));
    lw->AddSensor("Drivetrain", "left_encoder", drivetrainleft_encoder);
    drivetrainleft_encoder->SetDistancePerPulse(1.0);
    drivetrainleft_encoder->SetPIDSourceType(PIDSourceType::kRate);
    drivetrainright_encoder.reset(new Encoder(2, 3, false, Encoder::k4X));
    lw->AddSensor("Drivetrain", "right_encoder", drivetrainright_encoder);
    drivetrainright_encoder->SetDistancePerPulse(1.0);
    drivetrainright_encoder->SetPIDSourceType(PIDSourceType::kRate);


    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTORS
}
