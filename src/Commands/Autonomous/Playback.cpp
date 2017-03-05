#include "Playback.h"
#include <iostream>

Playback::Playback(std::string filePath) {
    this->filePath = filePath;
}

void Playback::Initialize() {
    RobotMap::drive_fl->SetTalonControlMode(CANTalon::TalonControlMode::kThrottleMode);
    RobotMap::drive_fr->SetTalonControlMode(CANTalon::TalonControlMode::kThrottleMode);
    RobotMap::drive_ml->SetTalonControlMode(CANTalon::TalonControlMode::kFollowerMode);
    RobotMap::drive_ml->Set(RobotMap::drive_fl->GetDeviceID());
    RobotMap::drive_mr->SetTalonControlMode(CANTalon::TalonControlMode::kFollowerMode);
    RobotMap::drive_mr->Set(RobotMap::drive_fr->GetDeviceID());
    RobotMap::drive_rl->SetTalonControlMode(CANTalon::TalonControlMode::kFollowerMode);
    RobotMap::drive_rl->Set(RobotMap::drive_fl->GetDeviceID());
    RobotMap::drive_rr->SetTalonControlMode(CANTalon::TalonControlMode::kFollowerMode);
    RobotMap::drive_rr->Set(RobotMap::drive_fr->GetDeviceID());
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
        while(getline(inputFile, line)){
            colon_pos = line.find(":");
            comma_pos = line.find(",");
            time_str = line.substr(0, colon_pos);
            left = line.substr(colon_pos+1, comma_pos-colon_pos-1);
            right = line.substr(comma_pos+1);
            playback_frame_buf.time = std::stod(time_str) / TIME_MULTIPLIER;
            playback_frame_buf.l = std::stod(left) * TIME_MULTIPLIER;
            playback_frame_buf.r = std::stod(right) * TIME_MULTIPLIER;
            playback_vec.push_back(playback_frame_buf);
        }
    }else{
        std::cout << "Why is the file not open? \n";
    }
    playback_vec.pop_back();

    timer.Reset();
    timer.Start();
}

void Playback::Execute() {
    if(t < playback_vec.size() && timer.Get() <= playback_vec.back().time) {
        while(t < playback_vec.size() && playback_vec[t].time <= timer.Get())
            t++;
        RobotMap::drive_fl->Set(playback_vec[t].l);
        RobotMap::drive_fr->Set(playback_vec[t].r);
    }else if(t == playback_vec.size() || timer.Get() > playback_vec.back().time){
        std::cout << "Done playing back \n";
        isFinished = true;
    }else{
        std::cout << "God help us, Playback does not work! \n";
        isFinished = true;
    }
}

bool Playback::IsFinished() {
    return isFinished;
}

void Playback::End() {
    RobotMap::drive_fl->Set(0);
    RobotMap::drive_fr->Set(0);
    std::cout << "Playback is over, you can rest easy (unless it didn't do what it was supposed to, then you gotta panick 'till the code is fixed) \n";
}

void Playback::Interrupted() {
    RobotMap::drive_fl->Set(0);
    RobotMap::drive_fr->Set(0);
    std::cout << "How the heck was Playback interrupted, it doesn't even require anything?! \n";
}
