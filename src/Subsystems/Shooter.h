#pragma once

#include "Commands/Subsystem.h"
#include "WPILib.h"
#include "CANTalon.h"

class Shooter: public Subsystem {
private:
    //std::shared_ptr<CANTalon> talon;

public:
    /*! \brief Constructor for shooter.
     *
     */
    Shooter();
    void InitDefaultCommand();
    /*! \brief  Spins the shooter
     * Sets speed of shooter to 'speed'
     * @param speed Speed of shooter
     */
    void Spin(float speed);
    /*! \brief Sets agitator
     *
     */
    void Agitate();
};
