#pragma once

#include "Commands/Command.h"
#include "../../Robot.h"
/*! \brief Allows the gunner to control the climber with the right joystick. */
class Climb: public Command {
public:
    Climb(); /*! Climb constructor. No special function. */

    virtual void Initialize(); /*! Climb initializer. No special function. */
    virtual void Execute(); /*! If the gunner's right joystick is pushed upwards, this will drive the climber with the strength at which the joystick is pushed. Else, the climber is stopped. */
    virtual bool IsFinished(); /*! Returns false. */
    virtual void End(); /*! Stops the climber. */
    virtual void Interrupted(); /*! Stops the climber. */
private:
    const double CURRENT_THRESHOLD = 4; //TODO remove or adjust and implement
};
