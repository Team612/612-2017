#pragma once

#include "WPILib.h"

/*!
    SetIntake Command

    Sets Intake to full speed in a certain direction for a certain time
*/

class SetIntake: public Command {
    bool clear;
public:
    /*! \brief Constructor for the SetIntake Command class

        @param timeout The Time SetIntake is scheduled to run
        @param clear Determines if the intake is running backwards (to clear jammed balls) or forwards (to intake balls). Is set to false by default
    */
    SetIntake(float timeout, bool clear = false);

    void Initialize() override;
    /*! \brief Runs continiously

        Called 60 times per second by WPILib until the timeout is reached.
        Sets in intake to the proper speed in the proper direction
    */
    void Execute() override;
    bool IsFinished() override;
    void End() override;
    void Interrupted() override;
};
