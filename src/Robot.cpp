#include "Robot.h"

#include "Commands/Shooter/SetShooter.h"
#include "Commands/Drive/Shift.h"
#include "Commands/Test/SystemCheck.h"
#include "Commands/Autonomous/Autonomous.h"
#include "Commands/Internal/IntakeFuel.h"
#include "lib612/Networking/Networking.h"

std::shared_ptr<Shooter> Robot::shooter;
std::shared_ptr<Drivetrain> Robot::drivetrain;
std::shared_ptr<Intake> Robot::intake;
std::shared_ptr<Climber> Robot::climber;
std::shared_ptr<Shifter> Robot::shifter;
std::shared_ptr<Vision> Robot::vision;
std::shared_ptr<LEDs> Robot::leds;
std::shared_ptr<GearSystem> Robot::gear_system;
std::unique_ptr<OI> Robot::oi;
std::shared_ptr<Hopper> Robot::shiftHopper;
std::unique_ptr<Command> Robot::CheckSystem;
std::unique_ptr<Command> Robot::intakeCommand;
std::unique_ptr<Command> Robot::playback;
std::unique_ptr<Command> Robot::testshooter;
std::unique_ptr<Command> Robot::shiftCommand;

frc::CameraServer* Robot::tempcam;
std::ofstream Robot::recordFile;
frc::Timer Robot::timer;

std::string Robot::filePath = "/home/lvuser/";

double Robot::initial_current;
double Robot::init_climber_current;

double Robot::drive_limit;

void Robot::RobotInit() {
    RobotMap::init();
    //using pointers the way C++ intended
    //subsystems
    shiftHopper = std::make_shared<Hopper>();
    shooter = std::make_shared<Shooter>();
    drivetrain.reset(new Drivetrain(new lib612::DriveProfile(1, 1, 1, 1, 1, 1, 0.1, 0.2, 0, 0))); //TODO actually use
    intake = std::make_shared<Intake>();
    climber = std::make_shared<Climber>();
    shifter = std::make_shared<Shifter>();
    vision = std::make_shared<Vision>();
    leds = std::make_shared<LEDs>();
    gear_system = std::make_shared<GearSystem>();
    //Put this last
    oi = std::make_unique<OI>();
    //commands
    CheckSystem = std::make_unique<SystemCheck>(); //#polymorphism
    //autonomousCommand = std::make_unique<Autonomous>();
    intakeCommand = std::make_unique<IntakeFuel>();
    //playback = std::make_unique<Playback>(filePath.c_str());
    testshooter = std::make_unique<SetShooter>(1000);

    //pdp
    initial_current = RobotMap::pdp->GetTotalCurrent();
    init_climber_current = RobotMap::pdp->GetCurrent(15);
    std::cout << "Info: Starting current: " << initial_current << std::endl;
    std::cout << "Info: Channel 15 current: " << init_climber_current << std::endl;

    //Global SmartDashboard capabilities
    //print time
    lib612::Networking::update_functions.push_back([]() {
        auto now = std::chrono::system_clock::now();
        auto to_time_t = std::chrono::system_clock::to_time_t(now);
        std::stringstream s;
        s << std::ctime(&to_time_t);
        SmartDashboard::PutString("Current Time", s.str());
    });
    //print intake current
    lib612::Networking::update_functions.push_back([](){
        frc::SmartDashboard::PutNumber("Total Intake Current", RobotMap::intake_talon_left->GetOutputCurrent() +
                                                               RobotMap::intake_talon_right->GetOutputCurrent());
    });
    //print shooter info
    lib612::Networking::update_functions.push_back([](){
        //frc::SmartDashboard::PutNumber("Shooter speed", RobotMap::shooter_l->GetSpeed());
        //frc::SmartDashboard::PutNumber("Shooter I Error", RobotMap::shooter_l->GetIaccum());
        //frc::SmartDashboard::PutNumber("I Zone", RobotMap::shooter_l->GetIzone());
        //frc::SmartDashboard::PutNumber("Shooter Error", RobotMap::shooter_l->GetClosedLoopError());
        frc::SmartDashboard::PutNumber("Shooter voltage", RobotMap::shooter_l->GetOutputVoltage());
        //frc::SmartDashboard::PutNumber("Shooter current", RobotMap::shooter_l->GetOutputCurrent());
        frc::SmartDashboard::PutNumber("Total Shooter Current", RobotMap::shooter_l->GetOutputCurrent());
    });
    //print drive current
    lib612::Networking::update_functions.push_back([](){
        frc::SmartDashboard::PutNumber("Total Drive Current", RobotMap::drive_ml->GetOutputCurrent() +
                                                              RobotMap::drive_fl->GetOutputCurrent() +
                                                              RobotMap::drive_rl->GetOutputCurrent() +
                                                              RobotMap::drive_mr->GetOutputCurrent() +
                                                              RobotMap::drive_fr->GetOutputCurrent() +
                                                              RobotMap::drive_rr->GetOutputCurrent());
    });
    //print climber info
    lib612::Networking::update_functions.push_back([](){
        //frc::SmartDashboard::PutNumber("Climber current", RobotMap::climber_srx->GetOutputCurrent());
        frc::SmartDashboard::PutNumber("Total Climber Current", RobotMap::climber_r->GetOutputCurrent() +
                                                                RobotMap::climber_l->GetOutputCurrent());
    });
    tempcam = CameraServer::GetInstance();
    tempcam->StartAutomaticCapture();

    drive_limit = 1.0;
    //default to Joe Mode
    SmartDashboard::PutBoolean("Joe Mode", true);
}

void Robot::DisabledInit() {
	if(shiftCommand.get() != nullptr) {
		shiftCommand->Cancel();
		shiftCommand.release();
	}
	shiftCommand = std::make_unique<Shift>(Shift::SHIFT_DIR::DOWN);
	shiftCommand->Start();

    RobotMap::drive_ml->SetTalonControlMode(CANTalon::TalonControlMode::kThrottleMode);
    RobotMap::drive_mr->SetTalonControlMode(CANTalon::TalonControlMode::kThrottleMode);
    RobotMap::drive_fl->SetTalonControlMode(CANTalon::TalonControlMode::kFollowerMode);
    RobotMap::drive_fl->Set(RobotMap::drive_ml->GetDeviceID());
    RobotMap::drive_fr->SetTalonControlMode(CANTalon::TalonControlMode::kFollowerMode);
    RobotMap::drive_fr->Set(RobotMap::drive_mr->GetDeviceID());
    //this->drive_fr->SetClosedLoopOutputDirection(true);
    RobotMap::drive_rl->SetTalonControlMode(CANTalon::TalonControlMode::kFollowerMode);
    RobotMap::drive_rl->Set(RobotMap::drive_ml->GetDeviceID());
    RobotMap::drive_rr->SetTalonControlMode(CANTalon::TalonControlMode::kFollowerMode);
    RobotMap::drive_rr->Set(RobotMap::drive_mr->GetDeviceID());
}

void Robot::DisabledPeriodic() {
    //lib612::Networking::UpdateAll();
    Scheduler::GetInstance()->Run();
}

void Robot::RobotPeriodic() {
    lib612::Networking::UpdateAll();
}

void Robot::AutonomousInit() {
	if(shiftCommand.get() != nullptr) {
		shiftCommand->Cancel();
		shiftCommand.release();
	}
	shiftCommand = std::make_unique<Shift>(Shift::SHIFT_DIR::DOWN);
	shiftCommand->Start();

    //get mp file
    ConfigureFilePath();
    //make new auto command with the correct auto mode
    autonomousCommand = std::make_unique<Autonomous>();

    //prevent segfaults
    if (autonomousCommand.get() != nullptr)
        autonomousCommand->Start();
    else
        std::cout << "ERROR: Autonomous Command NULL!" << std::endl;
    //AutoDrive->Start();
}

void Robot::AutonomousPeriodic() {
    //lib612::Networking::UpdateAll();
    Scheduler::GetInstance()->Run();
}
void Robot::TeleopInit() {
	if(shiftCommand.get() != nullptr) {
		shiftCommand->Cancel();
		shiftCommand.release();
	}
	shiftCommand = std::make_unique<Shift>(Shift::SHIFT_DIR::DOWN);
	shiftCommand->Start();

    // This makes sure that the autonomous stops running when
    // teleop starts running. If you want the autonomous to
    // continue until interrupted by another command, remove
    // these lines or comment it out.
    std::cout << "Robot.cpp: " << __LINE__ << std::endl;
    if (autonomousCommand.get() != nullptr)
        autonomousCommand->Cancel();
    if(frc::SmartDashboard::GetBoolean("debug", false))
        CheckSystem->Start();
    intakeCommand->Start();
}

void Robot::TeleopPeriodic() {
    //lib612::Networking::UpdateAll();
    //std::cout << "Robot.cpp: " << __LINE__ << std::endl;
    if(oi->getdriver()->GetBackButton())
        RobotMap::shooter_l->ClearIaccum();
    vision->PullValues();
    Scheduler::GetInstance()->Run();
    //std::cout << "Robot.cpp: " << __LINE__ << std::endl;
}

void Robot::TestInit() {
    //testshooter->Start();
    ConfigureFilePath();
    recordFile.open(filePath, std::ios::out | std::ios::app);
    std::cout << "Opening: " << filePath << std::endl;
    timer.Reset();
    timer.Start();
}

void Robot::TestPeriodic() {
    //lib612::Networking::UpdateAll();
    /*
     * How to record an autonomous mode
     * 1. Switch robot to Test
     * 2. Select desired autonomous mode on Even Smarter Dashboard
     * 3. Enable the robot and press B
     * 4. Disable the robot
     * 5. Enable the robot and drive while holding down the left bumper button (the robot assumes its on the red side)
     * 6 Disable the robot
     * 7. Switch the robot to autonomous mode
     * 8. Select the mode you recorded and indicate the alliance color
     * 9. Enable
     * 10. Cry
     */

    drivetrain->TankDrive(oi->getdriver()->GetSmoothY(frc::GenericHID::kLeftHand) * drive_limit, oi->getdriver()->GetSmoothY(frc::GenericHID::kRightHand) * drive_limit);

    if(oi->getdriver()->GetBumper(frc::GenericHID::kLeftHand) && recordFile.is_open()) {
        //kill me pls
        recordFile.close();
        recordFile.open(filePath, std::ios::out | std::ios::app);
        std::cout << timer.Get() << ":" << RobotMap::drive_ml->GetOutputVoltage() << "," << RobotMap::drive_mr->GetOutputVoltage() << "\n";
        recordFile << timer.Get() << ":" << RobotMap::drive_ml->GetOutputVoltage() << "," << RobotMap::drive_mr->GetOutputVoltage() << "\n";
    }
    if(oi->getdriver()->GetBButton()) {
        recordFile.close();
        recordFile.open(filePath, std::ios::trunc);
        std::cout << "File: " << filePath << " cleared!" << std::endl;
    }
    Scheduler::GetInstance()->Run();
}

void Robot::ConfigureFilePath() {
    filePath = "home/lvuser/";
    if(strcmp(frc::SmartDashboard::GetString("Chosen Autonomous Mode", "None").c_str(), "Simple") == 0){
        filePath+="simple";
    }else if(strcmp(frc::SmartDashboard::GetString("Chosen Autonomous Mode", "None").c_str(), "1 Gear Auto")== 0){
        filePath+="oneGearAuto";
    }else if(strcmp(frc::SmartDashboard::GetString("Chosen Autonomous Mode", "None").c_str(), "10 Ball Auto") == 0){
        filePath+="tenBallAuto";
    }else if(strcmp(frc::SmartDashboard::GetString("Chosen Autonomous Mode", "None").c_str(), "Full Gear Auto") == 0){
        filePath+="FGA";
    }else if(strcmp(frc::SmartDashboard::GetString("Chosen Autonomous Mode", "None").c_str(), "The Polymath") == 0){
        filePath+="polymath";
    }else if(strcmp(frc::SmartDashboard::GetString("Chosen Autonomous Mode", "None").c_str(), "Operation: Hopper Hack") == 0){
        filePath+="hophack";
    }else if(strcmp(frc::SmartDashboard::GetString("Chosen Autonomous Mode", "None").c_str(), "60 Ball Madlad Autonomous") == 0){
        filePath+="sixtyBallAuto";
    }else if(strcmp(frc::SmartDashboard::GetString("Chosen Autonomous Mode", "None").c_str(), "G.O.A.T") == 0){
        filePath+="GodHelpUsPlease";
    }else{
        filePath+="simple";
        std::cout << "Defaulted to simple auto \n";
    }
}

START_ROBOT_CLASS(Robot)

/*
 * Controls:
 * Gunner - X: Auto align left, B: Auto align right, Y: Cancel Auto align, Right Trigger: Intake, Left Bumper + Right trigger: Reverse intake,
 * Left stick: shoot (at boiler), Left stick + Start: Shoot (away from boiler), Right stick: climb
 * Driver - Joe Mode: Tank Drive, Ben Mode: Halo Drive, A: shift up, B: shift down, X: Toggle LEDs, Y: Change LED color
 */
