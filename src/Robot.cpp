#include "Robot.h"

std::shared_ptr<Shooter> Robot::shooter;
std::shared_ptr<Drivetrain> Robot::drivetrain;
std::shared_ptr<Conveyor> Robot::conveyor;
std::shared_ptr<Climber> Robot::climber;
std::unique_ptr<OI> Robot::oi;
std::shared_ptr<Command> Robot::AutoDrive;
std::shared_ptr<SystemCheck> Robot::CheckSystem;

void Robot::RobotInit() {
    RobotMap::init();
    shooter.reset(new Shooter());
    drivetrain.reset(new Drivetrain());
    conveyor.reset(new Conveyor());
    climber.reset(new Climber());
    oi.reset(new OI());
  }

void Robot::DisabledInit(){

}

void Robot::DisabledPeriodic() {
    Scheduler::GetInstance()->Run();
}

void Robot::AutonomousInit() {
    if (autonomousCommand.get() != nullptr)
        autonomousCommand->Start();
    AutoDrive->Start();

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
}

void Robot::TeleopPeriodic() {
    Scheduler::GetInstance()->Run();
}

void Robot::TestPeriodic() {
    lw->Run();
}

void Robot::TestInit() {
    CheckSystem->Run();
}

START_ROBOT_CLASS(Robot)
