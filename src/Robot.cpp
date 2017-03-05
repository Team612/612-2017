#include <lib612/DriveProfile.h>
#include "Robot.h"

#include <string>

#include "Commands/Test/SystemCheck.h"
#include "Commands/Autonomous/Autonomous.h"
#include "Commands/Drive/Wiggle.h"
#include "Commands/Internal/IntakeFuel.h"
#include "Commands/Autonomous/Playback.h"
#include "lib612/Networking/Networking.h"


std::shared_ptr<Shooter> Robot::shooter;
std::shared_ptr<Drivetrain> Robot::drivetrain;
std::shared_ptr<Intake> Robot::intake;
std::shared_ptr<Climber> Robot::climber;
std::shared_ptr<Shifter> Robot::shifter_subsys;
std::shared_ptr<Vision> Robot::vision;
std::shared_ptr<LEDs> Robot::leds;
std::unique_ptr<OI> Robot::oi;
std::unique_ptr<Command> Robot::CheckSystem;
std::unique_ptr<Command> Robot::wiggle;
std::unique_ptr<Command> Robot::intakeCommand;
std::unique_ptr<Command> Robot::playback;

std::string Robot::filePath = "/home/lvuser/";

double Robot::initial_current;
double Robot::init_climber_current;

void Robot::RobotInit() {
    RobotMap::init();
    //using pointers the way C++ intended
    //subsystems
    shooter = std::make_shared<Shooter>();
    drivetrain = std::make_shared<Drivetrain>(new lib612::DriveProfile(1, 1, 1, 1, 1, 1, 0.1, 0.2, 0, 0));
    intake = std::make_shared<Intake>();
    climber = std::make_shared<Climber>();
    shifter_subsys = std::make_shared<Shifter>();
    leds = std::make_shared<LEDs>();
    //Put this last
    oi = std::make_unique<OI>();
    std::cout << "Robot.cpp: " << __LINE__ << std::endl;
    //commands
    CheckSystem = std::make_unique<SystemCheck>(); //#polymorphism
    autonomousCommand = std::make_unique<Autonomous>();
    //wiggle = std::make_unique<Wiggle>(Wiggle::Direction::RIGHT);
    intakeCommand = std::make_unique<IntakeFuel>();
    ConfigureFilePath();
    //playback = std::make_unique<Playback>(filePath.c_str());

    //pdp
    initial_current = RobotMap::pdp->GetTotalCurrent();
    init_climber_current = RobotMap::pdp->GetCurrent(15);
    std::cout << "Info: Starting current: " << initial_current << std::endl;
    std::cout << "Info: Channel 15 current: " << init_climber_current << std::endl;

    //Put time on dashboard
    lib612::Networking::AddFunction([]() {
        auto now = std::chrono::system_clock::now();
        auto to_time_t = std::chrono::system_clock::to_time_t(now);
        std::stringstream s;
        s << std::ctime(&to_time_t);
        SmartDashboard::PutString("Current Time", s.str());
    });
  }

void Robot::DisabledInit() {

}

void Robot::DisabledPeriodic() {
    Scheduler::GetInstance()->Run();
}

void Robot::RobotPeriodic() {
    lib612::Networking::UpdateAll();
}

void Robot::AutonomousInit() {
    if (autonomousCommand.get() != nullptr)
        autonomousCommand->Start();
    //AutoDrive->Start();

}

void Robot::AutonomousPeriodic() {
    Scheduler::GetInstance()->Run();
}
void Robot::TeleopInit() {
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
    std::cout << "Robot.cpp: " << __LINE__ << std::endl;
}

void Robot::TeleopPeriodic() {
    //std::cout << "Robot.cpp: " << __LINE__ << std::endl;
    Scheduler::GetInstance()->Run();
    //std::cout << "Robot.cpp: " << __LINE__ << std::endl;
}

void Robot::TestInit() {

}

void Robot::TestPeriodic() {
    Scheduler::GetInstance()->Run();
}

void Robot::ConfigureFilePath(){
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
 * Gunner - X: full climb, Y: partial climb, Left bumper: grab, Right Bumper: Auto Align, Left Stick Y: Shoot, B: intake, A: slow outtake
 * Driver - Tank Drive
 */
