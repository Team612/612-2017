#pragma once

#include "Commands/Command.h"
#include "LiveWindow/LiveWindow.h"
#include "Timer.h"
#include "OI.h"
#include <fstream>

#include "RobotMap.h"
#include "Subsystems/Climber.h"
#include "Subsystems/Intake.h"
#include "Subsystems/Drivetrain.h"
#include "Subsystems/Shooter.h"
#include "Subsystems/Shifter.h"
#include "Subsystems/Vision.h"
#include "Subsystems/LEDs.h"
#include "Subsystems/Shifter.h"
#include "Subsystems/GearSystem.h"

class Robot : public IterativeRobot {
private:
    void ConfigureFilePath();
public:
    //global robot objects
    static std::string filePath;
    static std::ofstream recordFile;
    static frc::Timer timer;
    static frc::CameraServer* tempcam;
    static double drive_limit;

    //commands and subsystems
    std::unique_ptr<Command> autonomousCommand;
    static std::unique_ptr<OI> oi;
    LiveWindow* lw = LiveWindow::GetInstance();
    static std::shared_ptr<Shooter> shooter;
    static std::shared_ptr<Drivetrain> drivetrain;
    static std::shared_ptr<Intake> intake;
    static std::shared_ptr<Shifter> shifter;
    static std::shared_ptr<Climber> climber;
    static std::shared_ptr<Vision> vision;
    static std::shared_ptr<LEDs> leds;
    static std::shared_ptr<GearSystem> gear_system;
    static std::unique_ptr<Command> CheckSystem;
    static std::unique_ptr<Command> intakeCommand;
    static std::unique_ptr<Command> playback;
    static std::unique_ptr<Command> testshooter;
    static std::unique_ptr<Command> shiftCommand;
    static double initial_current;
    static double init_climber_current;

    //Iterative Robot overrides
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
