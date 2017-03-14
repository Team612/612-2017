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
    */
    void InitDefaultCommand() override;
    /*!
        \brief Sets the Intake talons to full speed
    */
    void IntakeFuel(); //intake with motor speed
    /*! \brief Reverses the intake subsystem to clear balls when jammed
    */
    void ClearBalls();
    /*! \breif Stops the intake
    */
    void Stop();
private:
    /*! Intake Speed constant, not currently used */
    const double INTAKE_SPEED = 1000;
    /*!Ramp rate constant in max volts*/
    const double RAMP_RATE = 16                                                                                                               ;
};
