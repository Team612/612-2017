#pragma once

#include "WPILib.h"
#include "../RobotMap.h"
#include "Commands/Subsystem.h"

/*! \brief Intake subsystem class for the intake subsystem on the robot
    Can Intake fuel, clear itself when jammed, and stop when required
    Implementsa ramp rate to prevent browning out the robot
*/

class Intake: public frc::Subsystem {
public:
    /*! \brief Intake class constructor

        Sets the talons on the intake subsystem to throttle mode (value between -1.0 and 1.0)
        Sets the ramp rate on the talons
        Sets one talon to follow mode
    */
    Intake();
    /*! \brief Initializes IntakeFuel as default command

        Sets IntakeFuel to the default command, constantly runs so that the robot can pick up balls as it runs over them
    */
    void InitDefaultCommand() override;
    /*! \brief Sets the Intake talons to full speed

        IntakeFuel is used by the IntakeFuel command found in Internal
    */
    void IntakeFuel(); //intake with motor speed
    /*! \brief Reverses the intake subsystem to clear balls when jammed

        Reverses the motors in the intake in an attempt to clear balls from the intake
    */
    void ClearBalls();
    /*! \brief Stops the intake

        Sets the intake motor values to zero
    */
    void Stop();
private:
    /*!
    Intake Speed constant, not currently used
    */
    const double INTAKE_SPEED = 1000;
    /*!
    Ramp rate constant in max volts
    */
    const double RAMP_RATE = 16                                                                                                               ;
};
