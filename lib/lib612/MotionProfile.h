#pragma once
#include <vector>

namespace lib612 {
    struct MotionProfile {
    /*
    Not to be confused with a drive profile
    MotionProfile stores target velocity for left and right at a specific timemark
    */
    std::vector<double> time;
    std::vector<double> leftRPM;
    std::vector<double> rightRPM;
    };
}
