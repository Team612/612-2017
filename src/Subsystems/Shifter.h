#pragma once

#include "WPILib.h"
#include "Commands/Subsystem.h"
#include "../RobotMap.h"


class Shifter: public frc::Subsystem {
public:
    /*! \brief Constructs Shifter
     * empty
     */
     Shifter();
     void InitDefaultCommand() override;
    /*! \brief Sets shifter to forward/up
     *
     */
     void ShiftUp();
    /*! \brief Sets shifter to reverse/down
     *
     */
     void ShiftDown();
    /*! \brief Sets shifter to off
     *
     */
     void ShiftOff();

private:

};
