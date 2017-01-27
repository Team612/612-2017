#include <WPILib.h>
#include <Joystick.h>
#include <SampleRobot.h>
#include <RobotDrive.h>
#include <Timer.h>
#include <CANTalon.h>
#include <CANSpeedController.h>
#include <XboxController.h>

class Robot: public frc::SampleRobot {
	
frc::XboxController controller { 1 };
CANTalon rl { 1 };
CANTalon rr { 7 };
CANTalon fl { 3 };
CANTalon fr { 4 };
frc::RobotDrive drive {fl,rl,fr,rr};

public:
	Robot() {
	
	}
		
	void RobotInit() {
		
	}
		
	void Autonomous() {
	
	}
	
	void OperatorControl() override{
		while(IsOperatorControl() && IsEnabled()) {
			drive.TankDrive(controller.GetY(frc::GenericHID::kLeftHand),controller.GetY(frc::GenericHID::kRightHand));
		}
	}	
	
	void Test() override {
		while(IsEnabled()) {
			frc::Wait(0.05);
		}
	}
	
};

START_ROBOT_CLASS(Robot)		
