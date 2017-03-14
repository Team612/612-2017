#pragma once

#include "WPILib.h"
#include "Commands/Command.h"
#include "../../Robot.h"

/*! \brief Intakes Fuel into the robot based on Joystick inputted

    This class differs from SetIntake in that this class sets the intake based on Joystick input for use in TeleOp
    Requires the intake subsystem
*/

class IntakeFuel: public Command {
public:
    /*! \brief Constructor for the IntakeFuel command

        Requires Intake subsystem
    */
    IntakeFuel();
    void Initialize() override;
    /*! \brief Controls the intake based on manual input

        When LB is pressed on the gunner controller, the intake reverses direction to clear balls
        When LB is not pressed, the intake intakes balls
    */
    void Execute() override;
    bool IsFinished() override;
    void End() override;
    void Interrupted() override;
private:
    bool in;
};
