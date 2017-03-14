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
#include "Subsystems/LEDs.h"
#include "Subsystems/Shifter.h"
#include "Timer.h"
#include "OI.h"

/*\brief Initializes the robot.
*/
class Robot : public IterativeRobot {
private:
    void ConfigureFilePath();
public:
    static std::string filePath;
    static frc::CameraServer* tempcam;

    std::unique_ptr<Command> autonomousCommand;
    static std::unique_ptr<OI> oi; /*! A pointer to the robot's OI, used to convey controller input.*/
    LiveWindow *lw = LiveWindow::GetInstance();
    std::shared_ptr<Shooter> Robot::shooter; /*! A pointer to the robot's Shooter subsystem.*/
    std::shared_ptr<Drivetrain> Robot::drivetrain; /*! A pointer to the robot's Drivetrain subsystem.*/
    std::shared_ptr<Intake> Robot::intake; /*! A pointer to the robot's Intake subsystem.*/
    std::shared_ptr<Climber> Robot::climber; /*! A pointer to the robot's Climber subsystem.*/
    std::shared_ptr<Shifter> Robot::shifter_subsys; /*! A pointer to the robot's Shifter subsystem.*/
    std::shared_ptr<Vision> Robot::vision; /*! A pointer to the robot's Vision subsystem.*/
    std::shared_ptr<LEDs> Robot::leds; /*! A pointer to the robot's LEDs.*/
    std::unique_ptr<Command> Robot::CheckSystem; /*! A pointer to a SystemCheck command, used for testing.*/
    std::unique_ptr<Command> Robot::wiggle; /*! A pointer to a Wiggle command. (Currently unused)*/
    std::unique_ptr<Command> Robot::intakeCommand; /*! A pointer to an IntakeFuel command, used to control the Intake motors.*/
    std::unique_ptr<Command> Robot::playback; /*! A pointer to a Playback command, used for Autonomous routines. (Currently unused) */
    std::unique_ptr<Command> Robot::testshooter; /*! A pointer to a SetShooter command, which sets the shooter to 1000 for testing purposes. */
    frc::CameraServer* Robot::tempcam; /*! A pointer to a CameraServer object. */
    static double initial_current;
    static double init_climber_current;
    virtual void RobotInit() override; /*! Initializes all of the robot's pointers, sets up PDP, and puts the time on the dashboard. */
    virtual void RobotPeriodic() override; /*! Updates Networking.*/
    virtual void DisabledInit() override; /*! No function.*/
    virtual void DisabledPeriodic() override; /*! Runs the Scheduler. */
    virtual void AutonomousInit() override; /*! Runs the Autonomous command. */
    virtual void AutonomousPeriodic() override; /*! Runs the Scheduler. */
    virtual void TeleopInit() override; /*! Ends the Autonomous command and prepares for teleop. */
    virtual void TeleopPeriodic() override; /*! Runs the Scheduler. */
    virtual void TestInit() override; /*! Tests the shooter. */
    virtual void TestPeriodic() override; /*! Allows the gunner to tune the shooter's PID while test routines are running.
                                              While the left bumper is held, values will increase, else, values will decrease.
                                              The A button will manipulate the P value.
                                              The B button will manipulate the I value.
                                              The X button will manipulate the D value.
                                              The Y button will manipulate the F value. */

};
