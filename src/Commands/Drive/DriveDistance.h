#pragma once

#include "Commands/Subsystem.h"
#include "../../Robot.h"

/*! \brief Drives the robot a set distance, as specified in the constructor. */
class DriveDistance: public PIDCommand {
public:
    DriveDistance(double distance); /*! Sets up the PID controller and converts the distance parameter into raw encoder units. */

    virtual void Initialize(); /*! Records the initial position of the encoders and enables the PID. */
    virtual void Execute(); /*! No function. */
    virtual bool IsFinished(); /*! Returns true when the PID controller is on target. */
    virtual void End();/*! Stops the drivetrain. */
    virtual void Interrupted();/*! Stops the drivetrain. */
    virtual double ReturnPIDInput(); /*! Returns the current distance from the starting point, in encoder units. */
    virtual void UsePIDOutput(double output); /*! Drives the drivetrain with the output of the PID controller. */

private:
    double pi = 3.141592653;

    double MAX_THROTTLE = 0.75; /*! The maximum throttle of the robot while it drives. */
    double distance; /*! The distance the robot will drive. Stored in raw encoder units. */
    double leftInitialDistance; /*! Stores the initial position of the left drivetrain encoder. */
    double rightInitialDistance; /*! Stores the initial position of the right drivetrain encoder. */
};
