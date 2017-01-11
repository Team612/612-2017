//This is an example file and can be removed

#include <iostream>
#include <memory>
#include <string>

#include <Joystick.h>
#include <SampleRobot.h>
#include <SmartDashboard/SendableChooser.h>
#include <SmartDashboard/SmartDashboard.h>
#include <RobotDrive.h>
#include <Timer.h>
#include <CanTalonSRX.h>

class Robot: public frc::SampleRobot {
	frc::RobotDrive myRobot { 0, 1 };
	frc::Joystick stick { 0 };
	CanTalonSRX actuator { 0 };

public:
	Robot() {
		myRobot.SetExpiration(0.1);
	}

	void RobotInit() {
		std::cout << "Robot enabled!" << std::endl;
	}

	void Autonomous() {
		auto timer = std::make_shared<Timer>();
		timer->Start();
		while(!IsOperatorControl() && IsEnabled()) {
			if(!(timer->Get() >= 10)) {
				myRobot.ArcadeDrive(0.4f, 0);
			} else {
				myRobot.ArcadeDrive((double) 0, 0);
				timer->Stop();
			}
		}
		std::cout << "Cleaning autonomous assets" << std::endl;
	}

	void OperatorControl() override {
		myRobot.SetSafetyEnabled(true);
		while (IsOperatorControl() && IsEnabled()) {
			myRobot.TankDrive(stick.GetRawAxis(1), stick.GetRawAxis(5));
			actuator.Set(stick.GetRawAxis(2));

			frc::Wait(0.005);
		}
	}

	void Test() override {
		while(IsEnabled()) {
			if(stick.GetRawButton(1)) {
				std::cout << "Button 1 lol" << std::endl;
			}
		}
	}
};

START_ROBOT_CLASS(Robot)
