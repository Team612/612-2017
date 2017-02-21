#include <lib612/DriveProfile.h>
#include "Robot.h"

#include "Commands/Drive/Drive.h"
#include "Commands/Test/SystemCheck.h"
#include "Commands/Test/TalonTest.h"
#include "Commands/Autonomous/Autonomous.h"
#include "Commands/Drive/Wiggle.h"
#include "lib612/Networking/Networking.h"

std::shared_ptr<Shooter> Robot::shooter;
std::shared_ptr<Drivetrain> Robot::drivetrain;
std::shared_ptr<Intake> Robot::intake;
std::shared_ptr<Climber> Robot::climber;
std::unique_ptr<OI> Robot::oi;
std::unique_ptr<Command> Robot::CheckSystem;
std::unique_ptr<Command> Robot::wiggle;

void Robot::RobotInit() {
    RobotMap::init();
    //using pointers the way C++ intended
    shooter = std::make_shared<Shooter>();
    drivetrain = std::make_shared<Drivetrain>(new lib612::DriveProfile(1, 1, 1, 1, 1, 1, 0.1, 0.2, 0, 0));
    intake = std::make_shared<Intake>();
    climber = std::make_shared<Climber>();
    oi = std::make_unique<OI>();
    CheckSystem = std::make_unique<SystemCheck>(); //#polymorphism
    autonomousCommand = std::make_unique<Autonomous>();
    wiggle = std::make_unique<Wiggle>(Wiggle::Direction::RIGHT);
  }

void Robot::DisabledInit(){

}

void Robot::DisabledPeriodic() {
    Scheduler::GetInstance()->Run();
}

void Robot::RobotPeriodic() {
    //update dashboard while robot is enabled in all modes
    if(IsEnabled())
        lib612::Networking::UpdateAll();
}

void Robot::AutonomousInit() {
    std::cout << "Choosing autonomous mode..." << std::endl;
    autonomousCommand = std::make_unique<Autonomous>();
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
    if (autonomousCommand.get() != nullptr)
        autonomousCommand->Cancel();
    if(frc::SmartDashboard::GetBoolean("debug", false)){
        CheckSystem->Start();
    }
}

void Robot::TeleopPeriodic() {
    Scheduler::GetInstance()->Run();
}

void Robot::TestInit() {


}

void Robot::TestPeriodic() {
    Scheduler::GetInstance()->Run();
}

START_ROBOT_CLASS(Robot)

/*
 * Controls:
 * Gunner - X: full climb, Y: partial climb, Left bumper: grab, Right Bumper: Auto Align, Left Stick Y: Shoot, B: intake, A: slow outtake
 * Driver - Tank Drive
 */
