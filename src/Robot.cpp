#include <iostream>
#include <memory>

#include <IterativeRobot.h>
#include <LiveWindow/LiveWindow.h>

#include <CANTalon.h>
#include <WPILib.h>
#include <vector>

class SmoothController : public XboxController {
	double GetSmoothed(double x) {
		// Quadratic curve that makes full power around 80%, half power around 35%
		double c = 0.2;
		double b = 0.6;
		double a = 0.0; // This should remain at 0 so that 0 is always 0
		if(x > 0)
			return (c * std::pow(x, 2)) + (b * x) + a;
		else
			return -((c * std::pow(x, 2)) + (b * abs(x)) + a); //reverse curve for negative values
	}
public:
	SmoothController(int port) : XboxController(port) {	}

	//x y trigger
	double GetSmoothX(frc::GenericHID::JoystickHand hand) {
		return GetSmoothed(GetX(hand));
	}
	double GetSmoothY(frc::GenericHID::JoystickHand hand) {
		return GetSmoothed(GetY(hand));
	}
	double GetSmoothTrigger(frc::GenericHID::JoystickHand hand) {
		return GetSmoothed(GetTriggerAxis(hand));
	}
};

using namespace frc;

class Robot: public IterativeRobot {
public:
//	CANTalon* shooter1;
//	CANTalon* shooter2;
//
//	CANTalon* intake1;
//	CANTalon* intake2;

	CANTalon* left1;
	CANTalon* left2;
	CANTalon* left3;
	CANTalon* right1;
	CANTalon* right2;
	CANTalon* right3;

//	CANTalon* climber1;

	SmoothController* driver;
	SmoothController* gunner;

    Compressor* compressor;
    DoubleSolenoid* solenoid;

//	double SHOOTER_SHOOT = -3200.0, SHOOTER_IDLE = -SHOOTER_SHOOT / 10, INTAKE = 1000,
	double RAMPRATE = 20;

	void RobotInit() {
        std::cout << "Starting Robot Code! (612-2017 SRX Current Limiting)" << std::endl;

		driver = new SmoothController(0);
		gunner = new SmoothController(1);

//		shooter1 = new CANTalon(7);
//		shooter2 = new CANTalon(8);
//
//		intake1 = new CANTalon(9);
//		intake2 = new CANTalon(10);
//
//		climber1 = new CANTalon(11);
//
//		shooter1->SelectProfileSlot(0);
//		shooter1->SetPID(0.1, 0.001, 4.1, 0.026);
//		shooter1->SetFeedbackDevice(CANTalon::FeedbackDevice::CtreMagEncoder_Relative);
//		shooter1->SetTalonControlMode(CANTalon::TalonControlMode::kSpeedMode);
//		shooter1->ConfigNominalOutputVoltage(+0.0f, -0.0f);
//		shooter1->ConfigPeakOutputVoltage(+12.0f, -12.0f);
//
//
//		shooter2->SetTalonControlMode(CANTalon::TalonControlMode::kFollowerMode);
//		shooter2->Set(shooter1->GetDeviceID());
//		shooter2->SetClosedLoopOutputDirection(true);
//
//		intake1->SelectProfileSlot(0);
//		intake1->SetPID(0.12, 0.001, 5, 0.08);
//		intake1->SetFeedbackDevice(CANTalon::FeedbackDevice::CtreMagEncoder_Relative);
//		intake1->SetTalonControlMode(CANTalon::TalonControlMode::kSpeedMode);
//		intake1->SetSensorDirection(false);
//		intake1->ConfigNominalOutputVoltage(+0.0f, -0.0f);
//		intake1->ConfigPeakOutputVoltage(+12.0f, -12.0f);
//
//		intake2->SetTalonControlMode(CANTalon::TalonControlMode::kFollowerMode);
//		intake2->Set(intake1->GetDeviceID());
//		intake2->SetClosedLoopOutputDirection(true);

		left1 = new CANTalon(3);
		left2 = new CANTalon(2);
		left3 = new CANTalon(1);

		left2->SetControlMode(CANSpeedController::ControlMode::kFollower);
		left2->Set(left1->GetDeviceID());
		left3->SetControlMode(CANSpeedController::ControlMode::kFollower);
		left3->Set(left1->GetDeviceID());

		right1 = new CANTalon(6);
		right2 = new CANTalon(5);
		right3 = new CANTalon(4);


		right2->SetControlMode(CANSpeedController::ControlMode::kFollower);
		right2->Set(right1->GetDeviceID());
		right3->SetControlMode(CANSpeedController::ControlMode::kFollower);
		right3->Set(right1->GetDeviceID());

		left1->SetCurrentLimit(40);
		left2->SetCurrentLimit(40);
		left3->SetCurrentLimit(40);
		right1->SetCurrentLimit(40);
		right2->SetCurrentLimit(40);
		right3->SetCurrentLimit(40);

		left1->EnableCurrentLimit(false);
		left2->EnableCurrentLimit(false);
		left3->EnableCurrentLimit(false);
		right1->EnableCurrentLimit(false);
		right2->EnableCurrentLimit(false);
		right3->EnableCurrentLimit(false);

        compressor =  new Compressor(3);
        solenoid = new DoubleSolenoid(0, 1);
        solenoid->Set(DoubleSolenoid::Value::kForward);

        compressor->Start();
	}

	void AutonomousInit() {
		std::cout << "Autonomous Init! (612-2017 SRX Current Limiting)" << std::endl;
    }

    void AutonomousPeriodic() {
    	std::cout << "Autonomous Periodic! (612-2017 SRX Current Limiting)" << std::endl;
    }

	void TeleopInit() {
		std::cout << "Teleop Init! (612-2017 SRX Current Limiting)" << std::endl;

		left1->SetTalonControlMode(CANTalon::TalonControlMode::kThrottleMode);
//		left1->SetVoltageRampRate(RAMPRATE);
		right1->SetTalonControlMode(CANTalon::TalonControlMode::kThrottleMode);
//		right1->SetVoltageRampRate(RAMPRATE);
    }

	bool lastA = false;
	bool isCurrentLimiting = false;

	void TeleopPeriodic() {
    	std::cout << "Teleop Periodic! (612-2017 templateREPLACEME)" << std::endl;

		double a = driver->GetSmoothY(frc::GenericHID::kLeftHand);
//		std::cout << "Left Y: " << a << std::endl;
		double b = driver->GetSmoothY(frc::GenericHID::kRightHand);
//		std::cout << "Right Y: " << b << std::endl;

		if(a > 0.1f || a < -0.1f) {
			left1->Set(a);
		} else {
			left1->SetVoltageRampRate(0);
			left1->Set(0);
//			left1->SetVoltageRampRate(RAMPRATE);
		}

		if(b > 0.1f || b < -0.1f) {
			right1->Set(-b);
		} else {
			right1->SetVoltageRampRate(0);
			right1->Set(0);
//			right1->SetVoltageRampRate(RAMPRATE);
		}

		if(driver->GetAButton() && !lastA) {
			isCurrentLimiting = !isCurrentLimiting;
			left1->EnableCurrentLimit(isCurrentLimiting);
			left2->EnableCurrentLimit(isCurrentLimiting);
			left3->EnableCurrentLimit(isCurrentLimiting);
			right1->EnableCurrentLimit(isCurrentLimiting);
			right2->EnableCurrentLimit(isCurrentLimiting);
			right3->EnableCurrentLimit(isCurrentLimiting);
		}

		lastA = driver->GetAButton();

		//std::printf("A: %d\n", gunner->GetAButton() ? 1 : 0);

//		if(gunner->GetAButton())
//			if(driver->GetStartButton())
//				shooter1->SetSetpoint(SHOOTER_SHOOT * 1.25);
//			else
//				shooter1->SetSetpoint(SHOOTER_SHOOT);
//		else
//			shooter1->SetSetpoint(SHOOTER_IDLE);

//		double c = gunner->GetSmoothTrigger(frc::GenericHID::kRightHand);

		//Drivers seemed to like this
//		std::cout << "Triggered: " << c << std::endl;
//		if(abs(c) > 0.1) {
//			if (gunner->GetBumper(frc::GenericHID::kLeftHand))
//				intake1->SetSetpoint(-INTAKE); // Allows us to clear intake
//			else
//				intake1->SetSetpoint(INTAKE);
//		} else {
//			intake1->SetSetpoint(0);
//		}

//		intake1->SetSetpoint(INTAKE);

//		double d = gunner->GetY(frc::GenericHID::kLeftHand);

//		if(d > 0.1f)
//			climber1->Set(-1);
//		else
//			climber1->Set(0);

		if(driver->GetBumper(frc::GenericHID::kLeftHand))
            solenoid->Set(DoubleSolenoid::Value::kForward);
        else if(driver->GetBumper(frc::GenericHID::kRightHand))
            solenoid->Set(DoubleSolenoid::Value::kReverse);
	}

    void DisabledInit() {
    	std::cout << "Disabled Init! (612-2017 templateREPLACEME)" << std::endl;
//        intake1->SetSetpoint(0);
    }
};

START_ROBOT_CLASS(Robot)
