#include "AnalogUltrasonic.h"

//consider smoothing
namespace lib612 {
    AnalogUltrasonic::AnalogUltrasonic(int port) : AnalogInput(port) { }

    double AnalogUltrasonic::GetLogDistanceInches() {
        return 20.52406 * std::log(GetVoltage()) + 57.11212;
    }

    double AnalogUltrasonic::GetLinearDistanceInches() {
        return 108.34706 * GetVoltage() - 2.95295;
    }
}
