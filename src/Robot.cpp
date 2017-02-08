#include "Robot.h"

#include "Commands/Drive/Drive.h"
#include "Commands/Test/SystemCheck.h"
#include "Commands/Test/TalonTest.h"
#include "Commands/Autonomous/Autonomous.h"

std::shared_ptr<Shooter> Robot::shooter;
std::shared_ptr<Drivetrain> Robot::drivetrain;
std::shared_ptr<Intake> Robot::intake;
std::shared_ptr<Climber> Robot::climber;
std::unique_ptr<OI> Robot::oi;
std::unique_ptr<Command> Robot::AutoDrive;
std::unique_ptr<Command> Robot::drivecommand;
std::unique_ptr<Command> Robot::CheckSystem;
std::unique_ptr<Command> Robot::talontesttest;

#define CHECK

void Robot::RobotInit() {
    RobotMap::init();
    //using pointers the way C++ intended
    shooter = std::make_shared<Shooter>();
    drivetrain = std::make_shared<Drivetrain>();
    intake = std::make_shared<Intake>();
    climber = std::make_shared<Climber>();
    oi = std::make_unique<OI>();
    drivecommand = std::make_unique<Drive>();
    CheckSystem = std::make_unique<SystemCheck>(); //#polymorphism
    talontesttest = std::make_unique<TalonTest>(2.f, .5f, TalonENUM::FR);
    autonomousCommand = std::make_unique<Autonomous>("THIS IS A PLACE HOLDER FOR RIGHT NOW");
  }

void Robot::DisabledInit(){

}

void Robot::DisabledPeriodic() {
    Scheduler::GetInstance()->Run();
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
    if (autonomousCommand.get() != nullptr)
        autonomousCommand->Cancel();
    #ifdef CHECK
        CheckSystem->Start();
    #endif
    drivecommand->Start(); //TODO: Investigate why default commands don't work
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
