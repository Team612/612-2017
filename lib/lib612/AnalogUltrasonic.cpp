#include "AnalogUltrasonic.h"

namespace lib612 {
    AnalogUltrasonic::AnalogUltrasonic(int port) : AnalogInput(port) { }
    double AnalogUltrasonic::GetDistanceMM() {
        return GetVoltage(); //TODO
    }

    double AnalogUltrasonic::GetDistanceInches() {
        //0.0248 Volts per inch
        return std::pow(0.0248, -1) * GetVoltage();
    }
}
