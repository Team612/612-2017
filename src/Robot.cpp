#include <lib612/DriveProfile.h>
#include "Robot.h"

#include <string>
#include <Commands/Shooter/SetShooter.h>

#include "Commands/Test/SystemCheck.h"
#include "Commands/Autonomous/Autonomous.h"
#include "Commands/Drive/Wiggle.h"
#include "Commands/Internal/IntakeFuel.h"
#include "Commands/Autonomous/Playback.h"
#include "lib612/Networking/Networking.h"

/*! \brief Initializes the robot and runs the robot's autonomous and teleoperative commands.
*/

std::shared_ptr<Shooter> Robot::shooter; /*! A pointer to the robot's Shooter subsystem.*/
std::shared_ptr<Drivetrain> Robot::drivetrain; /*! A pointer to the robot's Drivetrain subsystem.*/
std::shared_ptr<Intake> Robot::intake; /*! A pointer to the robot's Intake subsystem.*/
std::shared_ptr<Climber> Robot::climber; /*! A pointer to the robot's Climber subsystem.*/
std::shared_ptr<Shifter> Robot::shifter_subsys; /*! A pointer to the robot's Shifter subsystem.*/
std::shared_ptr<Vision> Robot::vision; /*! A pointer to the robot's Vision subsystem.*/
std::shared_ptr<LEDs> Robot::leds; /*! A pointer to the robot's LEDs.*/
std::unique_ptr<OI> Robot::oi; /*! A pointer to the robot's OI, used to convey controller input.*/
std::unique_ptr<Command> Robot::CheckSystem; /*! A pointer to a SystemCheck command, used for testing.*/
std::unique_ptr<Command> Robot::wiggle; /*! A pointer to a Wiggle command. (Currently unused)*/
std::unique_ptr<Command> Robot::intakeCommand; /*! A pointer to an IntakeFuel command, used to control the Intake motors.*/
std::unique_ptr<Command> Robot::playback; /*! A pointer to a Playback command, used for Autonomous routines. (Currently unused) */
std::unique_ptr<Command> Robot::testshooter; /*! A pointer to a SetShooter command, which sets the shooter to 1000 for testing purposes. */
frc::CameraServer* Robot::tempcam; /*! A pointer to a CameraServer object. */

std::string Robot::filePath = "/home/lvuser/"; /*! The default filepath for the robot to run from. */

double Robot::initial_current;
double Robot::init_climber_current;
/*! Initializes all of the robot's pointers, sets up PDP, and puts the time on the dashboard. */
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
    //autonomousCommand = std::make_unique<Autonomous>();
    //wiggle = std::make_unique<Wiggle>(Wiggle::Direction::RIGHT);
    intakeCommand = std::make_unique<IntakeFuel>();
    //playback = std::make_unique<Playback>(filePath.c_str());
    testshooter = std::make_unique<SetShooter>(1000);

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
    tempcam = CameraServer::GetInstance();
    tempcam->StartAutomaticCapture();
}

/*! No function.*/
void Robot::DisabledInit() {

}

/*! Runs the Scheduler. */
void Robot::DisabledPeriodic() {
    Scheduler::GetInstance()->Run();
}

/*! Updates Networking.*/
void Robot::RobotPeriodic() {
    lib612::Networking::UpdateAll();
}

/*! Runs the Autonomous command. */
void Robot::AutonomousInit() {
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
/*! Runs the Scheduler. */
void Robot::AutonomousPeriodic() {
    Scheduler::GetInstance()->Run();
}
/*! Ends the Autonomous command and prepares for teleop. */
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

/*! Runs the Scheduler. */
void Robot::TeleopPeriodic() {
    //std::cout << "Robot.cpp: " << __LINE__ << std::endl;
    Scheduler::GetInstance()->Run();
    //std::cout << "Robot.cpp: " << __LINE__ << std::endl;
}
/*! Tests the shooter. */
void Robot::TestInit() {
    testshooter->Start();
}
/*! Allows the gunner to tune the shooter's PID while test routines are running.
While the left bumper is held, values will increase, else, values will decrease.
The A button will manipulate the P value.
The B button will manipulate the I value.
The X button will manipulate the D value.
The Y button will manipulate the F value. */
void Robot::TestPeriodic() {
    if (oi->getgunner()->GetAButton()) {
        if(oi->getgunner()->GetBumper(frc::GenericHID::kLeftHand))
            frc::SmartDashboard::PutNumber("Test Shooter P", frc::SmartDashboard::GetNumber("Test Shooter P", 0) - 0.01);
        else
            frc::SmartDashboard::PutNumber("Test Shooter P", frc::SmartDashboard::GetNumber("Test Shooter P", 0) + 0.01);
    }
    if (oi->getgunner()->GetBButton()) {
        if(oi->getgunner()->GetBumper(frc::GenericHID::kLeftHand))
            frc::SmartDashboard::PutNumber("Test Shooter I", frc::SmartDashboard::GetNumber("Test Shooter I", 0) - 0.01);
        else
            frc::SmartDashboard::PutNumber("Test Shooter I", frc::SmartDashboard::GetNumber("Test Shooter I", 0) + 0.01);
    }
    if (oi->getgunner()->GetXButton()) {
        if(oi->getgunner()->GetBumper(frc::GenericHID::kLeftHand))
            frc::SmartDashboard::PutNumber("Test Shooter D", frc::SmartDashboard::GetNumber("Test Shooter D", 0) - 0.01);
        else
            frc::SmartDashboard::PutNumber("Test Shooter D", frc::SmartDashboard::GetNumber("Test Shooter D", 0) + 0.01);
    }
    if (oi->getgunner()->GetYButton()) {
        if(oi->getgunner()->GetBumper(frc::GenericHID::kLeftHand))
            frc::SmartDashboard::PutNumber("Test Shooter F", frc::SmartDashboard::GetNumber("Test Shooter F", 0) - 0.01);
        else
            frc::SmartDashboard::PutNumber("Test Shooter F", frc::SmartDashboard::GetNumber("Test Shooter F", 0) + 0.01);
    }

    Scheduler::GetInstance()->Run();
}
/*! Internal command which allows the AutonomousInit command to locate the user-chosen autonomous command. */
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
 * Gunner - X: full climb, Y: partial climb, Left bumper: grab, Right Bumper: Auto Align, Left Stick Y: Shoot, B: intake, A: slow outtake
 * Driver - Tank Drive
 */
