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
        if (x > 0)
            return std::min(D + ((A - D) / (1 + std::pow(x / C, B))), 1.0); //this function is like 1.0004 or something at x = 1
        else
            return std::max(-(D + ((A - D) / (1 + std::pow(-x / C, B)))), -1.0); //this function is like -1.0004 or something at x = -1
    }
}
