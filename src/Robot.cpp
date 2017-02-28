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
	
public:
	Robot() {
	
	}
		
	void RobotInit() {
		timer.Reset();
		fl.SetFeedbackDevice(CANTalon::FeedbackDevice::QuadEncoder);
		ml.SetFeedbackDevice(CANTalon::FeedbackDevice::QuadEncoder);
		rl.SetFeedbackDevice(CANTalon::FeedbackDevice::QuadEncoder);
		fr.SetFeedbackDevice(CANTalon::FeedbackDevice::QuadEncoder);
		mr.SetFeedbackDevice(CANTalon::FeedbackDevice::QuadEncoder);
		rr.SetFeedbackDevice(CANTalon::FeedbackDevice::QuadEncoder);
		frc::SmartDashboard::PutNumber("Time Multiplier", 1);
	}
		
	void Autonomous() {
		timer.Reset();
		timer.Start();
		timeMulti = frc::SmartDashboard::GetNumber("Time Multiplier", 1);
		fl.SetTalonControlMode(CANTalon::TalonControlMode::kThrottleMode);
		ml.SetTalonControlMode(CANTalon::TalonControlMode::kThrottleMode);
		rl.SetTalonControlMode(CANTalon::TalonControlMode::kThrottleMode);
		fr.SetTalonControlMode(CANTalon::TalonControlMode::kThrottleMode);
		mr.SetTalonControlMode(CANTalon::TalonControlMode::kThrottleMode);
		rr.SetTalonControlMode(CANTalon::TalonControlMode::kThrottleMode);
		std::ifstream mp;
		while(!mp.is_open()) {
			mp.open("/home/lvuser/mp");
			std::cout << "Opening mp\n";
			frc::Wait(1);
		}
		std::vector<double> time = {0};
		std::vector<double> l = {0};
		std::vector<double> r = {0};
		int colonPos = 0;
		int commaPos = 0;
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
		while(t < time.size() && timer.Get() < time.back()) {
			while(t < time.size() && time[t+1] < timer.Get()) {
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
		mp.open("/home/lvuser/mp",std::ofstream::out | std::ofstream::app);
		while(IsOperatorControl() && IsEnabled()) {
			fl.Set(-controller.GetY(frc::GenericHID::kLeftHand)/4);
			ml.Set(-controller.GetY(frc::GenericHID::kLeftHand)/4);
			rl.Set(-controller.GetY(frc::GenericHID::kLeftHand)/4);
			fr.Set(controller.GetY(frc::GenericHID::kRightHand)/4);
			mr.Set(controller.GetY(frc::GenericHID::kRightHand)/4);
			rr.Set(controller.GetY(frc::GenericHID::kRightHand)/4);
			if(controller.GetBButton()) {
				mp.close();
				mp.open("/home/lvuser/mp",std::ofstream::out | std::ofstream::trunc);
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
