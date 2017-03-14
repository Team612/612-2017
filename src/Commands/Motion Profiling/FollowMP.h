#pragma once

#include "lib612/MotionProfile.h"
#include "Commands/Command.h"
#include "../../Robot.h"
//! A class to execute MotionProfile
/*! \brief Execute MotionProfile
	Takes a MotionProfile as a constructor parameter
	Uses the Robot::drivetrain subsystem to follow MotionProfile
*/
class FollowMP: public Command {
public:
    FollowMP(lib612::MotionProfile* mp);
	
	//! Time counter variable
	/*! Used to scroll through the MotionProfile */
    unsigned int currentTimeMark;
	//! Timer object
	/*! Used to check the current time in relation to the MotionProfile.time vector */
    frc::Timer timer;
	//! MotionProfile object
	/*! MotionProfile object used to access motion profile data */
    lib612::MotionProfile* profile;
    virtual void Initialize();
	//! Execution of MotionProfile
	/*! Executes at 60 times a second to drive the Robot::drivetrain subsystem according the data */
    virtual void Execute();
    virtual bool IsFinished();
    virtual void End();
    virtual void Interrupted();
};
