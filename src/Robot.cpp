#include <lib612/DriveProfile.h>
#include "Robot.h"

#include "Commands/Drive/Drive.h"
#include "Commands/Test/SystemCheck.h"
#include "Commands/Test/TalonTest.h"
#include "Commands/Autonomous/Autonomous.h"
#include "Commands/Drive/Wiggle.h"
#include "lib612/Networking/Networking.h"
#include <chrono>

std::shared_ptr<Shooter> Robot::shooter;
std::shared_ptr<Drivetrain> Robot::drivetrain;
std::shared_ptr<Intake> Robot::intake;
std::shared_ptr<Climber> Robot::climber;
std::unique_ptr<OI> Robot::oi;
std::unique_ptr<Command> Robot::CheckSystem;
std::unique_ptr<Command> Robot::wiggle;
double Robot::initial_current;

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
    initial_current = RobotMap::pdp->GetTotalCurrent();
    std::cout << "Info: Starting current: " << initial_current << std::endl;
    std::cout << "Robot.cpp: " << __LINE__ << std::endl;
    lib612::Networking::AddFunction([](){
        std::cout << "Test" << std::endl;
        auto now = std::chrono::system_clock::now();
        auto to_time_t = std::chrono::system_clock::to_time_t(now);
        std::stringstream s;
        s << std::ctime(&to_time_t);
        SmartDashboard::PutString("Random time", s.str());
    });
    std::cout << "Robot.cpp: " << __LINE__ << std::endl;
  }

void Robot::DisabledInit() {
    std::cout << "Robot.cpp: " << __LINE__ << std::endl;
}

void Robot::DisabledPeriodic() {
    std::cout << "Robot.cpp: " << __LINE__ << std::endl;
    Scheduler::GetInstance()->Run();
    std::cout << "Robot.cpp: " << __LINE__ << std::endl;
}

void Robot::RobotPeriodic() {
    std::cout << "Robot.cpp: " << __LINE__ << std::endl;
    lib612::Networking::UpdateAll();
    std::cout << "Robot.cpp: " << __LINE__ << std::endl;
}

void Robot::AutonomousInit() {
    std::cout << "Robot.cpp: " << __LINE__ << std::endl;
    if (autonomousCommand.get() != nullptr)
        autonomousCommand->Start();
    //AutoDrive->Start();

}

void Robot::AutonomousPeriodic() {
    std::cout << "Robot.cpp: " << __LINE__ << std::endl;
    Scheduler::GetInstance()->Run();
}
void Robot::TeleopInit() {
    std::cout << "Robot.cpp: " << __LINE__ << std::endl;
    // This makes sure that the autonomous stops running when
    // teleop starts running. If you want the autonomous to
    // continue until interrupted by another command, remove
    // these lines or comment it out.
    if (autonomousCommand.get() != nullptr)
        autonomousCommand->Cancel();
    if(frc::SmartDashboard::GetBoolean("debug", false))
        CheckSystem->Start();
    std::cout << "Robot.cpp: " << __LINE__ << std::endl;
}

void Robot::TeleopPeriodic() {
    std::cout << "Robot.cpp: " << __LINE__ << std::endl;
    Scheduler::GetInstance()->Run();
    std::cout << "Robot.cpp: " << __LINE__ << std::endl;
}

void Robot::TestInit() {
    std::cout << "Robot.cpp: " << __LINE__ << std::endl;
}

void Robot::TestPeriodic() {
    std::cout << "Robot.cpp: " << __LINE__ << std::endl;
    Scheduler::GetInstance()->Run();
    std::cout << "Robot.cpp: " << __LINE__ << std::endl;
}

START_ROBOT_CLASS(Robot)

/*
 * Controls:
 * Gunner - X: full climb, Y: partial climb, Left bumper: grab, Right Bumper: Auto Align, Left Stick Y: Shoot, B: intake, A: slow outtake
 * Driver - Tank Drive
 */
