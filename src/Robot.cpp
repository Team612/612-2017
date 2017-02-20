#include <iostream>
#include <memory>
#include <string>

#include <IterativeRobot.h>
#include <LiveWindow/LiveWindow.h>
#include <SmartDashboard/SendableChooser.h>
#include <SmartDashboard/SmartDashboard.h>

#include <CANTalon.h>
#include <WPILib.h>
#include <XboxController.h>

#include <cmath>

using namespace frc;

class Robot: public IterativeRobot {
public:
	/* PID CONSTANTS
	3:1
	p = 0.1
	i = 0.001
	d = 4.1
	f = 0.026

	10:1
	p = 0.12
	i = 0.001
	d = 5
	f = 0.08
	*/

	CANTalon* shooter1;
	CANTalon* shooter2;
	CANTalon* intake1;
	CANTalon* intake2;
	CANTalon* left1;
	CANTalon* left2;
	CANTalon* left3;
	CANTalon* right1;
	CANTalon* right2;
	CANTalon* right3;
	CANTalon* climber1;
	XboxController *driver;
	XboxController* gunner;

	double SHOOTER_SHOOT = -3200.0, SHOOTER_IDLE = -SHOOTER_SHOOT / 5, INTAKE = 1000; // TODO: Intake value is garbage

	void RobotInit() {
		driver = new XboxController(0);
		gunner = new XboxController(1);

		shooter1 = new CANTalon(7);
		shooter2 = new CANTalon(8);

		intake1 = new CANTalon(9);
		intake2 = new CANTalon(10);

		climber1 = new CANTalon(11);

		shooter1->SelectProfileSlot(0);
		shooter1->SetPID(0.1, 0.001, 4.1, 0.026);
		shooter1->SetFeedbackDevice(CANTalon::FeedbackDevice::CtreMagEncoder_Relative);
		shooter1->SetTalonControlMode(CANTalon::TalonControlMode::kSpeedMode);
        shooter1->ConfigNominalOutputVoltage(+0.0f, -0.0f);
        shooter1->ConfigPeakOutputVoltage(+12.0f, -12.0f);


        shooter2->SetTalonControlMode(CANTalon::TalonControlMode::kFollowerMode);
        shooter2->Set(shooter1->GetDeviceID());
        shooter2->SetClosedLoopOutputDirection(true);

		intake1->SelectProfileSlot(0);
		intake1->SetPID(0.12, 0.001, 5, 0.08);
		intake1->SetFeedbackDevice(CANTalon::FeedbackDevice::CtreMagEncoder_Relative);
		intake1->SetTalonControlMode(CANTalon::TalonControlMode::kSpeedMode);
		intake1->SetSensorDirection(false);
		intake1->ConfigNominalOutputVoltage(+0.0f, -0.0f);
		intake1->ConfigPeakOutputVoltage(+12.0f, -12.0f);

        intake2->SetTalonControlMode(CANTalon::TalonControlMode::kFollowerMode);
        intake2->Set(intake1->GetDeviceID());
        intake2->SetClosedLoopOutputDirection(true);

		left1 = new CANTalon(1);
		left2 = new CANTalon(2);
		left3 = new CANTalon(3);
		left1->SetControlMode(CANSpeedController::ControlMode::kPercentVbus);

		left2->SetControlMode(CANSpeedController::ControlMode::kFollower);
		left2->Set(left1->GetDeviceID());
		left3->SetControlMode(CANSpeedController::ControlMode::kFollower);
		left3->Set(left1->GetDeviceID());

		right1 = new CANTalon(4);
		right2 = new CANTalon(5);
		right3 = new CANTalon(6);
		right1->SetControlMode(CANSpeedController::ControlMode::kPercentVbus);

		right2->SetControlMode(CANSpeedController::ControlMode::kFollower);
		right2->Set(right1->GetDeviceID());
		right3->SetControlMode(CANSpeedController::ControlMode::kFollower);
		right3->Set(right1->GetDeviceID());
	}

	void AutonomousInit() override {}
	void AutonomousPeriodic() {}

	void TeleopInit()
	{

	}


	void TeleopPeriodic() {
		double a = driver->GetY(frc::GenericHID::kLeftHand);
		double b = driver->GetY(frc::GenericHID::kRightHand);
		//std::printf("%f, %f\n", a, b);
		//std::printf("%f, %f\n", abs(a), abs(b));
			if(a > 0.1f || a < -0.1f){
				left1->Set(a);

			}
			else{
				left1->Set(0);

			}
			if(b > 0.1f || b < -0.1f){
				right1->Set(-b);

				}
			else{
				right1->Set(0);
			}
//		std::printf("%d\n", gunner->GetAButton() ? 1 : 0);

		if(gunner->GetAButton())
			shooter1->SetSetpoint(SHOOTER_SHOOT);
		else
			shooter1->SetSetpoint(SHOOTER_IDLE);


		std::printf("%d\n", gunner->GetBButton() ? 1 : 0);
		if(gunner->GetBButton())
			intake1->SetSetpoint(INTAKE);
		else
			intake1->SetSetpoint(0);

		double c = gunner->GetY(frc::GenericHID::kLeftHand);

		if(c > 0.05f || c < -0.05f){
			climber1->Set(c);
		}
		else{
			climber1->Set(0);
		}
	}
};

START_ROBOT_CLASS(Robot)
