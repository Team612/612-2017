#pragma once

#include "WPILib.h"

namespace lib612 {
    class AnalogUltrasonic : public AnalogInput {
        double GetLogDistanceInches();
        double GetLinearDistanceInches();
    public:
        AnalogUltrasonic(int port);
        double GetDistanceMM();
        double GetDistanceInches();
    };
}
