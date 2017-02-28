#pragma once

#include "WPILib.h"
#include "Commands/Command.h"
#include <vector>
#include <string>
#include "../../RobotMap.h"
#include <fstream>

class Playback: public Command {
private:
    struct playback_frame {
        double time;
        double l;
        double r;
    };

    bool isFinished;

    uint32_t t = 0;

    playback_frame playback_frame_buf;

    std::vector<playback_frame> playback_vec;

    std::string filePath;
    std::ifstream inputFile;

    frc::Timer timer;

    double l; //left speed
    double r; //right speed
    double next_update; //update

public:
    Playback(std::string filePath);
    void Initialize() override;
    void Execute() override;
    bool IsFinished() override;
    void End() override;
    void Interrupted() override;
};
