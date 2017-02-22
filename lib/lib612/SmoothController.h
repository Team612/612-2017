#include <WPILib.h>
namespace lib612 {
  class SmoothController : public XboxController {

  public:
  	SmoothController(int port);
  	double GetSmoothX(frc::GenericHID::JoystickHand hand);
  	double GetSmoothY(frc::GenericHID::JoystickHand hand);
  	double GetSmoothTrigger(frc::GenericHID::JoystickHand hand);

  private:
  	//quadratic curve that makes full power around 80%, half power around 35%

  	double c = 0.2;

  	double b = 0.6;

  	double a = 0.0; //this should remain at 0 so that 0 is always 0

  	double GetSmoothed(double x);

  };
}
