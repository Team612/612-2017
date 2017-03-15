#pragma once


#include "Commands/Command.h"
#include "../../Robot.h"
/*! \brief Allow the gunner to control the shooter with the joystick. Drives the shooter backwards at an idle speed when unused.
While the gunner's right joystick is pushed up, the shooter will spin at a rate proportional to the amount the stick is pushed.
While the driver has their START button pushed, the speed of the shooter will be increased by an additional START_MULTIPLIER. */
class Shoot: public Command {
public:
    Shoot(); /*! Constructor for shoot. */

    virtual void Initialize(); /*! Sets shooter to the idle speed. */
    virtual void Execute(); /*! Drives the shooter with the gunner's right joystick input, or sets it to idle while there is no input. */
    virtual bool IsFinished(); /*! Returns false. */
    virtual void End(); /*! Stops the shooter. */
    virtual void Interrupted(); /*! Stops the shooter. */

private:
    const double OPTIMAL_RPM = -3600; /*! The maximum speed of the shooter. */
    double IDLE = 1000; /*! The idle speed of the shooter. */
    const float START_MULTIPLIER = 1.25; /*! The multiplier applied to the shoot speed while the driver's start button is pressed. */
};
