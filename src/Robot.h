#pragma once
//TODO update TalonTest commmand to accomodate the two talons
#include "WPILib.h"
#include "Commands/Command.h"
#include "RobotMap.h"
#include "LiveWindow/LiveWindow.h"

#include "Subsystems/Climber.h"
#include "Subsystems/Intake.h"
#include "Subsystems/Drivetrain.h"
#include "Subsystems/Shooter.h"
#include "Timer.h"

#include "OI.h"

class Robot : public IterativeRobot {
public:
    std::unique_ptr<Command> autonomousCommand;
    static std::unique_ptr<OI> oi;
    LiveWindow *lw = LiveWindow::GetInstance();
    static std::shared_ptr<Shooter> shooter;
    static std::shared_ptr<Drivetrain> drivetrain;
    static std::shared_ptr<Intake> intake;
    static std::shared_ptr<Climber> climber;
    static std::unique_ptr<Command> AutoDrive;
    static std::unique_ptr<Command> drivecommand;
    static std::unique_ptr<Command> CheckSystem;
    static std::unique_ptr<Command> talontesttest;

    virtual void RobotInit();
    virtual void DisabledInit();
    virtual void DisabledPeriodic();
    virtual void AutonomousInit();
    virtual void AutonomousPeriodic();
    virtual void TeleopInit();
    virtual void TeleopPeriodic();
    virtual void TestInit();
    virtual void TestPeriodic();
};
