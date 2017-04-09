#include "Autonomous.h"
#include "AutoDrive.h"
#include "Playback.h"
#include "../Vision/AutoAlign.h"
#include "../Shooter/SetShooter.h"
#include "../Internal/SetIntake.h"
#include "../Internal/ToggleGear.h"

Autonomous::Autonomous() {
    auto chosen_mode = frc::SmartDashboard::GetString("Chosen Autonomous Mode", "None");
    std::cout << "Chosen Autonomous mode: " << chosen_mode << std::endl;
    AddSequential(new WaitCommand(1));
    std::cout << "Running: " << chosen_mode << std::endl;
    if(chosen_mode == "Simple") {
        AddSequential(new AutoDrive(5, 1));
        //TODO REMOVE!!
        //AddSequential(new Playback("home/lvuser/simple"));
    } else if(chosen_mode == "1 Gear Auto") {
        //drive up to the peg, place gear
        AddSequential(new Playback(Robot::filePath, !frc::SmartDashboard::GetBoolean("Red side", true)));
    } else if(chosen_mode == "10 Ball Auto") {
        //start at the boiler
        //Shoot for 15 seconds
        AddParallel(new SetShooter(-7.06), 10);
        AddParallel(new SetIntake(), 10);
        //TODO, replace with motion profile
        AddSequential(new WaitCommand(10));
        AddSequential(new AutoDrive(5, -.8f));
    } else if(chosen_mode == "Full Gear Auto") {
        //drive up to peg, place gear, wait 2 seconds, drive to loading station
        AddSequential(new Playback(Robot::filePath, !frc::SmartDashboard::GetBoolean("Red side", true)));
    } else if(chosen_mode == "The Polymath") {
        //place gear
        AddSequential(new Playback("/home/lvuser/oneGearAuto", !frc::SmartDashboard::GetBoolean("Red side", true)));
        AddSequential(new ToggleGear());
        AddSequential(new WaitCommand(2));
        AddSequential(new ToggleGear());
        //drive up to goal
        AddSequential(new Playback(Robot::filePath, !frc::SmartDashboard::GetBoolean("Red side", true)));
        //Align to target
        AddSequential(new AutoAlign(HorizontalFind::Direction::RIGHT));
        //Shoot for the rest of the time
        AddParallel(new SetShooter(-9), 30);
        AddParallel(new SetIntake(), 30);
    } else if(chosen_mode == "Operation: Hopper Hack") {
        //hack every hopper on the field
        AddSequential(new Playback(Robot::filePath, !frc::SmartDashboard::GetBoolean("Red side", true)));
    } else if(chosen_mode == "60 Ball Madlad Autonomous") {
        //Drive to hopper and activate it, wait for balls, drive back to goal
        AddSequential(new Playback(Robot::filePath, !frc::SmartDashboard::GetBoolean("Red side", true)));
        //Shoot for the rest of the time
        /*AddParallel(new SetShooter(30.0));
        AddParallel(new SetIntake(30));*/
    } else if(chosen_mode == "G.O.A.T.") {
        //NOTE: Same as 1 gear auto
        /*
         * drive up to the peg, place gear, wait 2 seconds, cross line, drive to hooper and activate it
         * wait for balls
         * Drive back to goal
         */
        AddSequential(new Playback(Robot::filePath, !frc::SmartDashboard::GetBoolean("Red side", true)));
        /*AddSequential(new AutoAlign(HorizontalFind::Direction::RIGHT));
        //Shoot for the rest of the time
        AddParallel(new SetShooter(30.0));
        AddParallel(new SetIntake(30));*/
    } else {
        std::cout << "Warning: Failed to choose autonomous mode! (Or none chosen)" << std::endl;
        std::cout << "Warning: Defaulting to simple auto" << std::endl;
        AddSequential(new AutoDrive(3, auto_speed));
    }
}
