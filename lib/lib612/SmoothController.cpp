#include "SmoothController.h"
namespace lib612 {
SmoothController::SmoothController(int port) : XboxController(port) {	}



	//x y trigger

double SmoothController::GetSmoothX(frc::GenericHID::JoystickHand hand) {

		return GetSmoothed(GetX(hand));

}

double SmoothController::GetSmoothY(frc::GenericHID::JoystickHand hand) {

		return GetSmoothed(GetY(hand));

}

double SmoothController::GetSmoothTrigger(frc::GenericHID::JoystickHand hand) {

		return GetSmoothed(GetTriggerAxis(hand));

}
double SmoothController::GetSmoothed(double x) {

		if(x > 0)

			return (c * std::pow(x, 2)) + (b * x) + a;

		else

			return -((c * std::pow(x, 2)) + (b * abs(x)) + a); //reverse curve for negative values

}

}
