#pragma once

#include "WPILib.h"

/*! \brief Turns LEDs on the robot on or off
    Turns LEDs on the robot on or off
*/

class LEDOnOff: public Command {

public:
    /*! \brief As SetState does not need to be called continously, this is where the code is

        If the LEDs are on, it turns them off. If the LEDs are off, it turns them on.
    */
    LEDOnOff();

    void Initialize() override;
    void Execute() override;

    /*! \brief Returns true because there is no instance in which this would not be finished when this function is called

        Returns true because there is no instance in which this would not be finished when this function is called
    */
    bool IsFinished() override;
    void End() override;
    void Interrupted() override;
};
