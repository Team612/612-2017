#pragma once

#include "Commands/Command.h"

/*! \brief Allows the driver to control the robot's drivetrain using the left and right sticks with a smoothed tank drive. */
class Drive: public Command {
public:
    Drive(); /*! Constructor for Drive. */

    virtual void Initialize(); /*! Intializes Drive. No fuction other than a printout notification. */
    virtual void Execute(); /*! Takes joystick input and uses it to drive the drivetrain via HaloDrive or TankDrive, after dampening it to 60% power. */
    virtual bool IsFinished(); /*! Returns false. */
    virtual void End(); /*! Sets the drivetrain to stop. */
    virtual void Interrupted(); /*! Sets the drivetrain to stop. */

private:

};
