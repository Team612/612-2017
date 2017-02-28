#pragma once

#include "WPILib.h"
#include "Commands/Command.h"
#include "RobotMap.h"
#include "LiveWindow/LiveWindow.h"

#include "Subsystems/Climber.h"
#include "Subsystems/Intake.h"
#include "Subsystems/Drivetrain.h"
#include "Subsystems/Shooter.h"
#include "Subsystems/Shifter.h"
#include "Subsystems/Vision.h"
#include "Timer.h"
#include "OI.h"
#include "Subsystems/Shifter.h"
class Robot : public IterativeRobot {
public:
    static std::string filePath;

    std::unique_ptr<Command> autonomousCommand;
    static std::unique_ptr<OI> oi;
    LiveWindow *lw = LiveWindow::GetInstance();
    static std::shared_ptr<Shooter> shooter;
    static std::shared_ptr<Drivetrain> drivetrain;
    static std::shared_ptr<Intake> intake;
    static std::shared_ptr<Shifter> shifter_subsys;
    static std::shared_ptr<Climber> climber;
    static std::shared_ptr<Vision> vision;
    static std::unique_ptr<Command> CheckSystem;
    static std::unique_ptr<Command> talontesttest;
    static std::unique_ptr<Command> wiggle; //defined by default with default values, reset it to something if you don't like that
    static std::unique_ptr<Command> intakeCommand;
    static std::unique_ptr<Command> playback;
    static double initial_current;
    static double init_climber_current;
    virtual void RobotInit() override;
    virtual void RobotPeriodic() override;
    virtual void DisabledInit() override;
    virtual void DisabledPeriodic() override;
    virtual void AutonomousInit() override;
    virtual void AutonomousPeriodic() override;
    virtual void TeleopInit() override;
    virtual void TeleopPeriodic() override;
    virtual void TestInit() override;
    virtual void TestPeriodic() override;
};
