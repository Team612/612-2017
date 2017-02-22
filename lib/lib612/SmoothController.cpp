#include "SmoothController.h"
namespace lib612 {
double SmoothController::GetSmoothed(double x) {

		if(x > 0)

			return (c * std::pow(x, 2)) + (b * x) + a;

		else

			return -((c * std::pow(x, 2)) + (b * abs(x)) + a); //reverse curve for negative values

	}
}
