#pragma once

#include <WPILib.h>

namespace lib612 {
  class SmoothController : public XboxController {

  public:
    SmoothController(int port);
    double GetSmoothX(frc::GenericHID::JoystickHand hand);
    double GetSmoothY(frc::GenericHID::JoystickHand hand);
    double GetSmoothTrigger(frc::GenericHID::JoystickHand hand);

  private:
    //specialized curve that makes full power 100%, half power around 20%
      const double A = 0.0;
      const double B = 2.675187;
      const double C = 159.0;
      const double D = 775000.0;

      double GetSmoothed(double x);
  };
}
