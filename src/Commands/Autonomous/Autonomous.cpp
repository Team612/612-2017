#include "Autonomous.h"
#include "AutoDrive.h"
#include "Playback.h"
#include "SimpleSideGear.h"
#include "../Vision/AutoAlign.h"
#include "../Shooter/SetShooter.h"
#include "../Internal/SetIntake.h"
#include "AutoDriveEnc.h"
#include <Commands/WaitCommand.h>

Autonomous::Autonomous() {
    auto chosen_mode = frc::SmartDashboard::GetString("Chosen Autonomous Mode", "None");
    std::cout << "Chosen Autonomous mode: " << chosen_mode << std::endl;
    //IMPORTANT: the mode is chosen when the command is created
    //TODO !!Replace empty initializer lists with correct marks for each mode!!
    AddSequential(new WaitCommand(1));
    if(chosen_mode == "Simple") {
        AddSequential(new AutoDrive(3, auto_speed));
        //TODO REMOVE!!
        //AddSequential(new Playback("home/lvuser/simple"));
    } else if(chosen_mode == "Enc") {
    	// TODO: Replace with real distance
    	AddSequential(new AutoDriveEnc(100, auto_speed));
    } else if(chosen_mode == "Simple Side Gear") {
        AddSequential(new SimpleSideGear(0.8, 10, !frc::SmartDashboard::GetBoolean("Red side", true)));
    } else if(chosen_mode == "1 Gear Auto") {
        //drive up to the peg, place gear
        AddSequential(new Playback(Robot::filePath, !frc::SmartDashboard::GetBoolean("Red side", true)));
    } else if(chosen_mode == "10 Ball Auto") {
        //drive up to hopper
        AddSequential(new Playback(Robot::filePath, !frc::SmartDashboard::GetBoolean("Red side", true)));
        //Align to target
        AddSequential(new AutoAlign(HorizontalFind::Direction::RIGHT));
        //Shoot for 5 seconds
        AddParallel(new SetShooter(5));
        AddParallel(new SetIntake(5));
        //cross line
        AddSequential(new Playback(Robot::filePath, !frc::SmartDashboard::GetBoolean("Red side", true))); //TODO this requires a second motion profile
    } else if(chosen_mode == "Full Gear Auto") {
        //drive up to peg, place gear, wait 2 seconds, drive to loading station
        AddSequential(new Playback(Robot::filePath, !frc::SmartDashboard::GetBoolean("Red side", true)));
    } else if(chosen_mode == "The Polymath") {
        //NOTE: Same as 10 ball auto
        //drive up to hopper
        AddSequential(new Playback(Robot::filePath, !frc::SmartDashboard::GetBoolean("Red side", true)));
        //Align to target
        AddSequential(new AutoAlign(HorizontalFind::Direction::RIGHT));
        //Shoot for 5 seconds
        AddParallel(new SetShooter(5.0));
        AddParallel(new SetIntake(5));
        //NOTE: Same as full gear auto
        //drive up to peg, place gear, wait 2 seconds, drive 2 loading station
        AddSequential(new Playback(Robot::filePath, !frc::SmartDashboard::GetBoolean("Red side", true))); //TODO this requires a second motion profile
    } else if(chosen_mode == "Operation: Hopper Hack") {
        //hack every hopper on the field
        AddSequential(new Playback(Robot::filePath, !frc::SmartDashboard::GetBoolean("Red side", true)));
    } else if(chosen_mode == "60 Ball Madlad Autonomous") {
        //Drive to hopper and activate it, wait for balls, drive back to goal
        AddSequential(new Playback(Robot::filePath, !frc::SmartDashboard::GetBoolean("Red side", true)));
        //Shoot for the rest of the time
        AddParallel(new SetShooter(30.0));
        AddParallel(new SetIntake(30));
    } else if(chosen_mode == "G.O.A.T.") {
        //NOTE: Same as 1 gear auto
        /*
         * drive up to the peg, place gear, wait 2 seconds, cross line, drive to hooper and activate it
         * wait for balls
         * Drive back to goal
         */
        AddSequential(new Playback(Robot::filePath, !frc::SmartDashboard::GetBoolean("Red side", true)));
        AddSequential(new AutoAlign(HorizontalFind::Direction::RIGHT));
        //Shoot for the rest of the time
        AddParallel(new SetShooter(30.0));
        AddParallel(new SetIntake(30));
    } else {
        std::cout << "Warning: Failed to choose autonomous mode! (Or none chosen)" << std::endl;
        std::cout << "Warning: Defaulting to simple auto" << std::endl;
        AddSequential(new AutoDrive(auto_time, auto_speed));
    }
}
