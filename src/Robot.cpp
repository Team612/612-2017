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
	//CANTalon* shooter2;
	CANTalon* intake1;
	//CANTalon* intake2;
	CANTalon* left1;
	CANTalon* left2;
	CANTalon* left3;
	CANTalon* right1;
	CANTalon* right2;
	CANTalon* right3;
	XboxController *driver;
	XboxController* gunner;

	double SHOOTER_SHOOT = -3200.0, SHOOTER_IDLE = -3200.0 / 5, INTAKE = 1000; // TODO: Intake value is garbage

	void RobotInit() {
		driver = new XboxController(0);
		gunner = new XboxController(1);

		shooter1 = new CANTalon(0);
		//shooter2 = new CANTalon(0);
		intake1 = new CANTalon(1);
		//intake2 = new CANTalon(1);

        shooter1->SetFeedbackDevice(CANTalon::FeedbackDevice::CtreMagEncoder_Relative);
        shooter1->SetControlMode(frc::CANSpeedController::ControlMode::kSpeed);
        shooter1->SetSensorDirection(false);
        shooter1->ConfigNominalOutputVoltage(+0.0f, -0.0f);
        shooter1->ConfigPeakOutputVoltage(+12.0f, 0.0f);
        shooter1->SelectProfileSlot(0);
        shooter1->SetPID(0.1, 0.001, 4.1, 0.026);

        //shooter2->SetControlMode(CANSpeedController::ControlMode::kFollower);
        //shooter2->Set(0); // SAME AS ID FOR SHOOTER 1

        intake1->SetFeedbackDevice(CANTalon::FeedbackDevice::CtreMagEncoder_Relative);
        intake1->SetControlMode(frc::CANSpeedController::ControlMode::kSpeed);
        intake1->SetSensorDirection(false);
        intake1->ConfigNominalOutputVoltage(+0.0f, -0.0f);
        intake1->ConfigPeakOutputVoltage(+12.0f, 0.0f);
        intake1->SelectProfileSlot(0);
        intake1->SetPID(0.12, 0.001, 5, 0.08);

        //intake2->SetControlMode(CANSpeedController::ControlMode::kFollower);
        //intake2->Set(1); // SAME AS ID FOR INTAKE 1

		left1 = new CANTalon(2);
		left2 = new CANTalon(3);
		left3 = new CANTalon(4);

		left2->SetControlMode(CANSpeedController::ControlMode::kFollower);
		left2->Set(2); // SAME AS ID FOR LEFT 1
		left3->SetControlMode(CANSpeedController::ControlMode::kFollower);
		left3->Set(2); // SAME AS ID FOR LEFT 1

		right1 = new CANTalon(5);
		right2 = new CANTalon(6);
		right3 = new CANTalon(7);

		right2->SetControlMode(CANSpeedController::ControlMode::kFollower);
		right2->Set(5); // SAME AS ID FOR RIGHT 1
		right3->SetControlMode(CANSpeedController::ControlMode::kFollower);
		right3->Set(5); // SAME AS ID FOR RIGHT 1
	}

	void AutonomousInit() override {}
	void AutonomousPeriodic() {}

	void TeleopInit()
	{
		if(gunner->GetAButton())
			shooter1->Set(SHOOTER_SHOOT);
		else
			shooter1->Set(SHOOTER_IDLE);

		if(gunner->GetBButton())
			intake1->Set(INTAKE);
		else
			intake1->Set(0);
	}

	void TeleopPeriodic() {

	}
};

START_ROBOT_CLASS(Robot)
