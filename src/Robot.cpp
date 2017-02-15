#include <lib612/DriveProfile.h>
#include "Robot.h"

#include "Commands/Test/SystemCheck.h"
#include "Commands/Autonomous/Autonomous.h"

std::shared_ptr<Shooter> Robot::shooter;
std::shared_ptr<Drivetrain> Robot::drivetrain;
std::shared_ptr<Intake> Robot::intake;
std::shared_ptr<Climber> Robot::climber;
std::unique_ptr<OI> Robot::oi;
std::unique_ptr<Command> Robot::CheckSystem;

void Robot::RobotInit() {
    RobotMap::init();
    //using pointers the way C++ intended
    shooter = std::make_shared<Shooter>();
    drivetrain = std::make_shared<Drivetrain>(new lib612::DriveProfile(1, 1, 1, 1, 1, 1));
    intake = std::make_shared<Intake>();
    climber = std::make_shared<Climber>();
    oi = std::make_unique<OI>();
    CheckSystem = std::make_unique<SystemCheck>(); //#polymorphism
  }

void Robot::DisabledInit(){

}

void Robot::DisabledPeriodic() {
    Scheduler::GetInstance()->Run();
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
