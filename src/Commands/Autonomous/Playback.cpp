#include "Playback.h"

Playback::Playback(std::string filePath, bool reverse) {
    this->filePath = filePath;
    this->reverse = reverse;
}

void Playback::Initialize() {
    RobotMap::drive_ml->SetVoltageRampRate(0);
    RobotMap::drive_mr->SetVoltageRampRate(0);
    //RobotMap::drive_ml->SetVoltageCompensationRampRate(0);
    //RobotMap::drive_mr->SetVoltageCompensationRampRate(0);

    RobotMap::drive_ml->Set(0);
    RobotMap::drive_mr->Set(0);


    RobotMap::drive_ml->SetTalonControlMode(CANTalon::TalonControlMode::kVoltageMode);
    RobotMap::drive_mr->SetTalonControlMode(CANTalon::TalonControlMode::kVoltageMode);

    RobotMap::drive_fl->SetTalonControlMode(CANTalon::TalonControlMode::kFollowerMode);
    RobotMap::drive_fl->Set(RobotMap::drive_ml->GetDeviceID());
    RobotMap::drive_fr->SetTalonControlMode(CANTalon::TalonControlMode::kFollowerMode);
    RobotMap::drive_fr->Set(RobotMap::drive_mr->GetDeviceID());
    RobotMap::drive_rl->SetTalonControlMode(CANTalon::TalonControlMode::kFollowerMode);
    RobotMap::drive_rl->Set(RobotMap::drive_ml->GetDeviceID());
    RobotMap::drive_rr->SetTalonControlMode(CANTalon::TalonControlMode::kFollowerMode);
    RobotMap::drive_rr->Set(RobotMap::drive_mr->GetDeviceID());

    inputFile.open(filePath);

    if(inputFile.is_open()) {
        std::cout << "Reading file at " << filePath << std::endl;
        std::string line;
        std::string time_str;
        std::string left;
        std::string right;
        unsigned long colon_pos = 0;
        unsigned long comma_pos = 0;
        //GET DATA FROM INPUT FILE
        while(getline(inputFile, line)){
            colon_pos = line.find(":");
            comma_pos = line.find(",");
            time_str = line.substr(0, colon_pos);
            left = line.substr(colon_pos+1, comma_pos-colon_pos-1);
            right = line.substr(comma_pos+1);
            //std::cout << __LINE__ << ": Time string - " << time_str << std::endl;
            playback_frame_buf.time = std::stod(time_str) / TIME_MULTIPLIER;
            //std::cout << __LINE__ << ": Left - " << left << std::endl;
            playback_frame_buf.l = std::stod(left) * TIME_MULTIPLIER;
            //std::cout << __LINE__ << ": Right - " << right << std::endl;
            playback_frame_buf.r = std::stod(right) * TIME_MULTIPLIER;
            //std::cout << __LINE__ << std::endl;
            playback_vec.push_back(playback_frame_buf);
        }
    }else{
        std::cout << "Why is the file not open? \n";
    }
    playback_vec.pop_back();

    t = 0;

    timer.Reset();
    timer.Start();

    isFinished = false;

    do {
        if(reverse) {
            RobotMap::drive_ml->Set(-playback_vec[t].r);
            RobotMap::drive_mr->Set(playback_vec[t].l);
        } else {
            RobotMap::drive_ml->Set(-playback_vec[t].l);
            RobotMap::drive_mr->Set(playback_vec[t].r);
        }

        if(!frc::DriverStation::GetInstance().IsEnabled() || !frc::DriverStation::GetInstance().IsAutonomous()) {
            isFinished = true;
            break;
        }

        RobotMap::drive_fl->Set(RobotMap::drive_ml->GetDeviceID());
        RobotMap::drive_rl->Set(RobotMap::drive_ml->GetDeviceID());

        RobotMap::drive_fr->Set(RobotMap::drive_mr->GetDeviceID());
        RobotMap::drive_rr->Set(RobotMap::drive_mr->GetDeviceID());

        std::cout << "Get() " << RobotMap::drive_ml->Get() << "," << RobotMap::drive_mr->Get() << std::endl;
        std::cout << "GetOutputVoltage() " << RobotMap::drive_ml->GetOutputVoltage() << "," << RobotMap::drive_mr->GetOutputVoltage() << std::endl;
        std::cout << "t: " << t << std::endl << "size: " << playback_vec.size() << std::endl;

        if(timer.Get() >= playback_vec[t + 1].time)
            t++;

        if (t >= playback_vec.size() || timer.Get() > playback_vec.back().time) {
            std::cout << "Done playing back \n";
            isFinished = true;
        }
    } while(!isFinished);
}

void Playback::Execute() {  }

bool Playback::IsFinished() {
    return isFinished;
}

void Playback::End() {
    RobotMap::drive_fl->SetVoltageRampRate(0);
    RobotMap::drive_fr->SetVoltageRampRate(0);
    RobotMap::drive_fl->Set(0);
    RobotMap::drive_fr->Set(0);
    std::cout << "Playback is over, you can rest easy (unless it didn't do what it was supposed to, then you gotta panic 'till the code is fixed) \n";
    RobotMap::drive_ml->SetTalonControlMode(CANTalon::TalonControlMode::kThrottleMode);
    RobotMap::drive_mr->SetTalonControlMode(CANTalon::TalonControlMode::kThrottleMode);
    timer.Stop();
    timer.Reset();
}

void Playback::Interrupted() {
    RobotMap::drive_fl->SetVoltageRampRate(0);
    RobotMap::drive_fr->SetVoltageRampRate(0);
    RobotMap::drive_fl->Set(0);
    RobotMap::drive_fr->Set(0);
    std::cout << "How the heck was Playback interrupted, it doesn't even require anything?! \n";
    RobotMap::drive_ml->SetTalonControlMode(CANTalon::TalonControlMode::kThrottleMode);
    RobotMap::drive_mr->SetTalonControlMode(CANTalon::TalonControlMode::kThrottleMode);
    timer.Stop();
    timer.Reset();
}
