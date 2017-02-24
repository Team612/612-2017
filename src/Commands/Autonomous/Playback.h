#pragma once

#include "WPILib.h"
#include <vector>

class Playback : public Command {
public:
    Playback(std::vector<double> times, std::vector<double> left, std::vector<double> right, bool invert = false);
    void Initialize() override;
    void Execute() override;
    bool IsFinished() override;
    void End() override;
    void Interrupted() override;
private:
    std::vector<double> time_mark;
    std::vector<double> left_setpoints;
    std::vector<double> right_setpoints;
    double is_inverted;
    Timer* timer;
};

