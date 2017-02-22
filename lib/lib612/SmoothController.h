#include <WPILib.h>

namespace lib612 {
class SmoothController : public XboxController {

	//quadratic curve that makes full power around 80%, half power around 35%
public:
	double c = 0.2;

	double b = 0.6;

	double a = 0.0; //this should remain at 0 so that 0 is always 0

	double GetSmoothed(double x);
};
}
