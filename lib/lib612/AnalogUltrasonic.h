#pragma once

#include "WPILib.h"

namespace lib612 {
    class AnalogUltrasonic : public AnalogInput {
    public:
        AnalogUltrasonic(int port);
        double GetDistanceMM();
        double GetLogDistanceInches();
        double GetLinearDistanceInches();
    };
}
