#include <WPILib.h>
#include <Joystick.h>
#include <SampleRobot.h>
#include <RobotDrive.h>
#include <Timer.h>
#include <CANTalon.h>
#include <CANSpeedController.h>
#include <XboxController.h>
#include <Timer.h>
#include <vector>

class Robot: public frc::SampleRobot {

frc::XboxController controller { 0 };
CANTalon rr { 1 };
CANTalon rl { 2 };
CANTalon fl { 3 };
CANTalon fr { 4 };
frc::RobotDrive drive {fl,rl,fr,rr};
std::vector<double> time = {0, 0.5, 1, 1.5, 2, 2.5, 3, 3.5, 4, 4.5, 5};
std::vector<double> Vl = {0, 100, 200, 300, 400, 500, 400, 300, 200, 100, 0};
std::vector<double> Vr = {0, 100, 200, 300, 400, 500, 400, 300, 200, 100, 0};
frc::Timer timer {};

public:
	Robot() {

	}

	void RobotInit() {
		rl.SetInverted(true);
	}

	void Autonomous() {
		rr.SetFeedbackDevice(CANTalon::QuadEncoder);
		fl.SetFeedbackDevice(CANTalon::QuadEncoder);
		rr.SetSensorDirection(true);
		rr.SetPID(0.75, 0.0, 0.0, 1.0);
		fl.SetPID(0.75, 0.0, 0.0, 1.0);
		fl.SetTalonControlMode(CANTalon::TalonControlMode::kSpeedMode);
		rr.SetTalonControlMode(CANTalon::TalonControlMode::kSpeedMode);
		fr.SetTalonControlMode(CANTalon::TalonControlMode::kFollowerMode);
		
		rl.SetTalonControlMode(CANTalon::TalonControlMode::kFollowerMode);
		int t = 0;
		timer.Reset();
		timer.Start();
		while(t <= Vl.size()) {
			frc::SmartDashboard::PutNumber("rr position", rr.GetPosition());
			frc::SmartDashboard::PutNumber("rr speed", rr.GetSpeed());
			frc::SmartDashboard::PutNumber("fl position", fl.GetPosition());
			frc::SmartDashboard::PutNumber("fl speed", fl.GetSpeed());
			fl.SetSetpoint(Vl[t]);
			rr.SetSetpoint(Vr[t]);
			fr.Set(1);
			rl.Set(3);
			while(t < Vl.size() && time[t+1] < timer.Get()) {
				t++;
			}
		}
	}

	void OperatorControl() override{
		rr.SetFeedbackDevice(CANTalon::QuadEncoder);
		fl.SetFeedbackDevice(CANTalon::QuadEncoder);
		rr.SetSensorDirection(true);
		rr.SetPID(0.75, 0.0, 0.0, 1.0);
		fl.SetPID(0.75, 0.0, 0.0, 1.0);
		
		while(IsOperatorControl() && IsEnabled()) {
			frc::SmartDashboard::PutNumber("rr position", rr.GetPosition());
			frc::SmartDashboard::PutNumber("rr speed", rr.GetSpeed());
			frc::SmartDashboard::PutNumber("fl position", fl.GetPosition());
			frc::SmartDashboard::PutNumber("fl speed", fl.GetSpeed());
			drive.TankDrive(-controller.GetY(frc::GenericHID::kLeftHand),-controller.GetY(frc::GenericHID::kRightHand));
		}
	}

	void Test() override {
		while(IsEnabled()) {
			frc::Wait(0.05);
		}
	}

};

START_ROBOT_CLASS(Robot)
