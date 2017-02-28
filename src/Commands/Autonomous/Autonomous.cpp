#include "Autonomous.h"
#include "AutoDrive.h"
#include "Playback.h"
#include "../Vision/AutoAlign.h"
#include "../Shooter/SetShooter.h"
#include "../Internal/IntakeFuel.h"

Autonomous::Autonomous() {
    auto chosen_mode = frc::SmartDashboard::GetString("Chosen Autonomous Mode", "");
    std::cout << "Chosen Autonomous mode: " << chosen_mode << std::endl;
    //IMPORTANT: the mode is chosen when the command is created
    //TODO !!Replace empty initializer lists with correct marks for each mode!!
    if(chosen_mode == "Simple") {
        AddSequential(new AutoDrive(auto_time, auto_speed));
    } else if(chosen_mode == "1 Gear Auto") {
        //drive up to the peg, place gear
        AddSequential(new Playback(Robot::filePath));
        //Wait 2 seconds
        AddSequential(new frc::WaitCommand(2));
        //cross line
        AddSequential(new Playback(Robot::filePath));
    } else if(chosen_mode == "10 Ball Auto") {
        //drive up to hopper
        AddSequential(new Playback(Robot::filePath));
        //Align to target
        AddSequential(new AutoAlign(HorizontalFind::Direction::RIGHT));
        //Shoot for 5 seconds
        AddParallel(new SetShooter(5.0));
        AddParallel(new IntakeFuel(true), 5);
        //cross line
        AddSequential(new Playback(Robot::filePath));
    } else if(chosen_mode == "Full Gear Auto") {
        //drive up to peg, place gear
        AddSequential(new Playback(Robot::filePath));
        //wait 2 seconds
        AddSequential(new frc::WaitCommand(2));
        //drive to loading station
        AddSequential(new Playback(Robot::filePath));
    } else if(chosen_mode == "The Polymath") {
        //NOTE: Same as 10 ball auto
        //drive up to hopper
        AddSequential(new Playback(Robot::filePath));
        //Align to target
        AddSequential(new AutoAlign(HorizontalFind::Direction::RIGHT));
        //Shoot for 5 seconds
        AddParallel(new SetShooter(5.0));
        AddParallel(new IntakeFuel(true), 5);
        //NOTE: Same as full gear auto
        //drive up to peg, place gear
        AddSequential(new Playback(Robot::filePath));
        //wait 2 seconds
        AddSequential(new frc::WaitCommand(2));
        //drive to loading station
        AddSequential(new Playback(Robot::filePath));
    } else if(chosen_mode == "Operation: Hopper Hack") {
        //hack every hopper on the field
        AddSequential(new Playback(Robot::filePath));
    } else if(chosen_mode == "60 Ball Madlad Autonomous") {
        //Drive to hopper and activate it
        AddSequential(new Playback(Robot::filePath));
        //Wait for balls to fill robot
        AddSequential(new frc::WaitCommand(3));
        //Drive back to goal
        AddSequential(new Playback(Robot::filePath));
        //Shoot for the rest of the time
        AddParallel(new SetShooter(30.0));
        AddParallel(new IntakeFuel(true), 30);
    } else if(chosen_mode == "G.O.A.T.") {
        //NOTE: Same as 1 gear auto
        //drive up to the peg, place gear
        AddSequential(new Playback(Robot::filePath));
        //Wait 2 seconds
        AddSequential(new frc::WaitCommand(2));
        //cross line
        //NOTE Same as 60 ball madlad autonomous
        //Drive to hopper and activate it
        AddSequential(new Playback(Robot::filePath));
        //Wait for balls to fill robot
        AddSequential(new frc::WaitCommand(3));
        //Drive back to goal
        AddSequential(new Playback(Robot::filePath));
        //Align to target
        AddSequential(new AutoAlign(HorizontalFind::Direction::RIGHT));
        //Shoot for the rest of the time
        AddParallel(new SetShooter(30.0));
        AddParallel(new IntakeFuel(true), 30);
    } else {
        std::cout << "Error: Failed to choose autonomous mode!" << std::endl;
        std::cout << "Warning: Defaulting to simple auto" << std::endl;
        AddSequential(new AutoDrive(auto_time, auto_speed));
    }
}
