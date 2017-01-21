#pragma once

#include "WPILib.h"
#include "Commands/Command.h"
#include "RobotMap.h"
#include "LiveWindow/LiveWindow.h"

#include "Subsystems/Climber.h"
#include "Subsystems/Conveyor.h"
#include "Subsystems/Drivetrain.h"
#include "Subsystems/Shooter.h"

#include "OI.h"

class Robot : public IterativeRobot {
public:
	std::unique_ptr<Command> autonomousCommand;
	static std::unique_ptr<OI> oi;
	LiveWindow *lw = LiveWindow::GetInstance();
    static std::shared_ptr<Shooter> shooter;
    static std::shared_ptr<Drivetrain> drivetrain;
    static std::shared_ptr<Conveyor> conveyor;
    static std::shared_ptr<Climber> climber;

	virtual void RobotInit();
	virtual void DisabledInit();
	virtual void DisabledPeriodic();
	virtual void AutonomousInit();
	virtual void AutonomousPeriodic();
	virtual void TeleopInit();
	virtual void TeleopPeriodic();
	virtual void TestPeriodic();
};
