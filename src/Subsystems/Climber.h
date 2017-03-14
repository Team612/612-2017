#pragma once

#include "Commands/Subsystem.h"
#include "../RobotMap.h"
#include "WPILib.h"

class Climber: public Subsystem {
private:
public:
    /*! \brief Constructor for the Climber class
        Takes no arguments
    */
    Climber();
    /*! \brief Initializes Default Command, built into WPILib
        Sets the default command to climb
    */
    void InitDefaultCommand();
    /*! \brief Moves the climber
        @param Speed to move the climber at, between -1.0 and 1.0
    */
    void Move(float speed); //drive climber at speed
    /*! \brief Stops the climber
        Sets the left climber talon to zero, right climber talon should be in follow mode
    */
    void Block();
    /*! \brief A Servo was initially used to grab the rope, we no longer do this
        Unused
    */
    void Grab(double position); //TODO get rid of this
};
