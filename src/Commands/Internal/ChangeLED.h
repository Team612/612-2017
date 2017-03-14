#pragma once

#include "WPILib.h"

/*! \brief Class for toggling the color of the LEDs on the robot

    Requires the LED subsystem
*/

class ChangeLED: public Command {

public:
    /*! \brief Constructor for the ChangeLED command

        Requires the LED subsystem
    */
    ChangeLED();

    /*! \brief Toggles the color of the LED

        As ToggleColor does not need to be called continously, this is where the code is
    */
    void Initialize() override;
    void Execute() override;
    
    /*! \brief Returns true because there is no instance in which this would not be finished when this function is called

        Returns true because there is no instance in which this would not be finished when this function is called
    */
    bool IsFinished() override;
    void End() override;
    void Interrupted() override;
};
