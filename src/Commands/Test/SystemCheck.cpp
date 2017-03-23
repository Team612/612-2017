#include "../../Robot.h"
#include "SystemCheck.h"
#include "Commands/WaitCommand.h"
#include "TalonTest.h"

SystemCheck::SystemCheck() {
    //Interrupt all other commands using these subsystems
    Requires(Robot::drivetrain.get());
    Requires(Robot::climber.get());
    Requires(Robot::shooter.get());
    Requires(Robot::intake.get());
    //NOTE: Talons in follow mode are commented out
    AddSequential(new TalonTest( 2.0f,  0.5f, TalonENUM::SHOOTER_L));
    AddSequential(new TalonTest( 2.0f,  -0.5f, TalonENUM::SHOOTER_L));
    //AddSequential(new TalonTest( 2.0f,  -0.5f, TalonENUM::SHOOTER_R));
    AddSequential(new TalonTest( 2.0f,  -0.5f, TalonENUM::CLIMBER)); // only one climber now
    //AddSequential(new TalonTest( 2.0f,  -0.5f, TalonENUM::CLIMBER_R));
    //AddSequential(new TalonTest( 2.0f,  0.5f, TalonENUM::INTAKE_L));
    //AddSequential(new TalonTest( 2.0f,  -0.5f, TalonENUM::INTAKE_L));
    AddSequential(new TalonTest( 2.0f,  0.5f, TalonENUM::INTAKE_R));
    AddSequential(new TalonTest( 2.0f,  -0.5f, TalonENUM::INTAKE_R));
    //AddSequential(new TalonTest( 2.0f,  0.5f, TalonENUM::FL));
    //AddSequential(new TalonTest( 2.0f,  -0.5f, TalonENUM::FL));
    AddSequential(new TalonTest( 2.0f,  0.5f, TalonENUM::ML));
    AddSequential(new TalonTest( 2.0f,  -0.5f, TalonENUM::ML));
    //AddSequential(new TalonTest( 2.0f,  0.5f, TalonENUM::RL));
    //AddSequential(new TalonTest( 2.0f,  -0.5f, TalonENUM::RL));
    //AddSequential(new TalonTest( 2.0f,  0.5f, TalonENUM::FR));
    //AddSequential(new TalonTest( 2.0f,  -0.5f, TalonENUM::FR));
    AddSequential(new TalonTest( 2.0f,  0.5f, TalonENUM::MR));
    AddSequential(new TalonTest( 2.0f,  -0.5f, TalonENUM::MR));
    //AddSequential(new TalonTest( 2.0f,  0.5f, TalonENUM::RR));
    //AddSequential(new TalonTest( 2.0f,  -0.5f, TalonENUM::RR));
}
