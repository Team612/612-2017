#include "Playback.h"
#include <iostream>

Playback::Playback(std::string filePath) {
    this->filePath = filePath;

}

void Playback::Initialize() {
    RobotMap::drive_fl->SetTalonControlMode(CANTalon::TalonControlMode::kThrottleMode);
    RobotMap::drive_fr->SetTalonControlMode(CANTalon::TalonControlMode::kThrottleMode);
    RobotMap::drive_ml->SetTalonControlMode(CANTalon::TalonControlMode::kFollowerMode);
    RobotMap::drive_mr->SetTalonControlMode(CANTalon::TalonControlMode::kFollowerMode);
    RobotMap::drive_rl->SetTalonControlMode(CANTalon::TalonControlMode::kFollowerMode);
    RobotMap::drive_rr->SetTalonControlMode(CANTalon::TalonControlMode::kFollowerMode);
    inputFile.open(filePath);
    if(inputFile.is_open()) {
        std::cout << "Reading file at " << filePath << std::endl;
        std::string line;
        std::string time_str;
        std::string left;
        std::string right;
        int colon_pos = 0;
        int comma_pos = 0;
        //GET DATA FROM INPUT FILE
        while(getline(inputFile, line))
        {
            colon_pos = line.find(":");
            comma_pos = line.find(",");
            time_str = line.substr(0, colon_pos);
            left = line.substr(colonPos+1, comma_pos-colon_pos-1);
            right = line.substr(comma_pos+1);
            playback_frame_buf.time = std::stod(time_str);
            playback_frame_buf.l = std::stod(left);
            playback_frame_buf.r = std::stod(right);
            playback_vec.push_back(playback_frame_buf);
        }
    }

    timer.Reset();
    timer.Start();
}

void Playback::Execute() {

}

bool Playback::IsFinished() {
    return false;
}

void Playback::End() {

}

void Playback::Interrupted() {

}
