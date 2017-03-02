#include <WPILib.h>
#include <Joystick.h>
#include <SampleRobot.h>
#include <RobotDrive.h>
#include <Timer.h>
#include <CANTalon.h>
#include <CANSpeedController.h>
#include <XboxController.h>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>

class Robot: public frc::SampleRobot {
	
frc::XboxController controller { 0 };
CANTalon fl { 3 };
CANTalon ml { 2 };
CANTalon rl { 1 };
CANTalon fr { 6 };
CANTalon mr { 5 };
CANTalon rr { 4 };
frc::Timer timer;
double timeMulti = 1;
double driveMulti = 1;
double inverse = 0;

std::string GetOutputPath() {
	std::ifstream profile_reader;

	//load the profile of the correct mode
	std::string file = "/home/lvuser/";
	auto current_mode = frc::SmartDashboard::GetString("Chosen Autonomous Mode", "None");
	//make sure we do nothing if the auto mode is set to none
	if(current_mode == "None")
		return "";

	//file conventions consistent with master
	if(current_mode == "Simple")
		file += "simple";
	else if(current_mode == "1 Gear Auto")
		file += "oneGearAuto";
	else if(current_mode == "10 Ball Auto")
		file += "tenBallAuto";
	else if(current_mode == "Full Gear Auto")
		file += "FGA";
	else if(current_mode == "The Polymath")
		file += "polymath";
	else if(current_mode == "Operation: Hopper Hack")
		file += "hophack";
	else if(current_mode == "60 Ball Madlad Autonomous")
		file += "sixtyBallAuto";
	else if(current_mode == "G.O.A.T.")
		file += "GodHelpUsPlease";
	else {
		std::cout << "ERROR: Chosen Auto mode not recognized" << std::endl;
		return "";
	}
	return file;
}
	
public:
	Robot() = default;
		
	void RobotInit() {
		timer.Reset();
		fl.SetFeedbackDevice(CANTalon::FeedbackDevice::QuadEncoder);
		ml.SetFeedbackDevice(CANTalon::FeedbackDevice::QuadEncoder);
		rl.SetFeedbackDevice(CANTalon::FeedbackDevice::QuadEncoder);
		fr.SetFeedbackDevice(CANTalon::FeedbackDevice::QuadEncoder);
		mr.SetFeedbackDevice(CANTalon::FeedbackDevice::QuadEncoder);
		rr.SetFeedbackDevice(CANTalon::FeedbackDevice::QuadEncoder);
		frc::SmartDashboard::PutNumber("Time Multiplier", 4);
		frc::SmartDashboard::PutNumber("Drive Multiplier", 0.25);
		frc::SmartDashboard::PutNumber("Inverse", 1);
	}
		
	void Autonomous() {
		timer.Reset();
		timer.Start();
		timeMulti = frc::SmartDashboard::GetNumber("Time Multiplier", 4);
		fl.SetTalonControlMode(CANTalon::TalonControlMode::kThrottleMode);
		ml.SetTalonControlMode(CANTalon::TalonControlMode::kThrottleMode);
		rl.SetTalonControlMode(CANTalon::TalonControlMode::kThrottleMode);
		fr.SetTalonControlMode(CANTalon::TalonControlMode::kThrottleMode);
		mr.SetTalonControlMode(CANTalon::TalonControlMode::kThrottleMode);
		rr.SetTalonControlMode(CANTalon::TalonControlMode::kThrottleMode);
		std::ifstream mp;
		while(!mp.is_open()) {
			if(GetOutputPath() != "")
				mp.open(GetOutputPath());
			std::cout << "Opening mp\n";
			frc::Wait(1);
		}
		std::vector<double> time = {0};
		std::vector<double> l = {0};
		std::vector<double> r = {0};
		unsigned long colonPos = 0;
		unsigned long commaPos = 0;
		std::string timeString;
		std::string leftString;
		std::string rightString;
		std::string line;
		if(mp.is_open()) {
			std::cout << "Reading mp \n";
			while(getline(mp,line)) {
				colonPos = line.find(":");
				commaPos = line.find(",");
				timeString = line.substr(0,colonPos);
				leftString = line.substr(colonPos+1,commaPos-colonPos-1);
				rightString = line.substr(commaPos+1);
				time.push_back(std::stod(timeString)/timeMulti);
				l.push_back(std::stod(leftString)*timeMulti);
				r.push_back(std::stod(rightString)*timeMulti);
			}
		}
		unsigned int t = 0;
		std::cout << "Running mp \n";
		time.pop_back();
		r.pop_back();
		l.pop_back();
		while(t < time.size() && timer.Get() <= time.back()) {
			while(t < time.size() && timer.Get() <= time.back() && time[t+1] < timer.Get()) {
				t++;
			}
			fl.Set(l[t]);
			ml.Set(l[t]);
			rl.Set(l[t]);
			fr.Set(r[t]);
			mr.Set(r[t]);
			rr.Set(r[t]);
			std::cout << time[t] << ":" << l[t] << "," << r[t] << "\n";
		}
		mp.close();
	}
	
	void OperatorControl() override{
		timer.Reset();
		timer.Start();
		fl.SetTalonControlMode(CANTalon::TalonControlMode::kThrottleMode);
		ml.SetTalonControlMode(CANTalon::TalonControlMode::kThrottleMode);
		rl.SetTalonControlMode(CANTalon::TalonControlMode::kThrottleMode);
		fr.SetTalonControlMode(CANTalon::TalonControlMode::kThrottleMode);
		mr.SetTalonControlMode(CANTalon::TalonControlMode::kThrottleMode);
		rr.SetTalonControlMode(CANTalon::TalonControlMode::kThrottleMode);
		std::ofstream mp;
		if(GetOutputPath() != "")
			mp.open(GetOutputPath(),std::ofstream::out | std::ofstream::app);
		while(IsOperatorControl() && IsEnabled()) {
			driveMulti = frc::SmartDashboard::GetNumber("Drive Multiplier", 0.25);
			inverse = frc::SmartDashboard::GetNumber("Inverse",1);
            double forward = -controller.GetY(frc::GenericHID::kLeftHand);
			if(std::abs(forward) < 0.02) {
				forward = 0;
			}
            double rotation = -controller.GetX(frc::GenericHID::kRightHand);
			if(std::abs(rotation) < 0.02) {
				rotation = 0;
			}
            double left, right;
            if (forward > 0.0) {
                if (rotation > 0.0) {
                    left = forward - rotation;
                    right = std::max(forward, rotation);
                } else {
                    left = std::max(forward, -rotation);
                    right = forward + rotation;
                }
            } else {
                if (rotation > 0.0) {
                    left = -std::max(-forward, rotation);
                    right = forward + rotation;
                } else {
                    left = forward - rotation;
                    right = -std::max(-forward, -rotation);
                }
            }
			left = left * driveMulti;
			right = -right * driveMulti;
			if(inverse == 1) {
            	ml.Set(left); fl.Set(left); rl.Set(left);
            	mr.Set(right); fr.Set(right); rr.Set(right);
			}
			else {
				ml.Set(right); fl.Set(right); rl.Set(right);
            	mr.Set(left); fr.Set(left); rr.Set(left);
			}
            std::cout << driveMulti << " Set raw left: " << left << "; Set raw right: " << right << std::endl;
			if(controller.GetBButton()) {
				mp.close();
				if(GetOutputPath() != "")
					mp.open(GetOutputPath(), std::ofstream::trunc);
			}
			if(controller.GetBumper(frc::GenericHID::kLeftHand) && mp.is_open()) {
				mp << timer.Get() << ":" << fl.GetOutputVoltage()/fl.GetBusVoltage() << "," << fr.GetOutputVoltage()/fr.GetBusVoltage() << "\n";
			}
		}
		mp.close();
	}	
	
	void Test() override {
		while(IsEnabled()) {
			frc::Wait(0.05);
		}
	}
};

START_ROBOT_CLASS(Robot)		
