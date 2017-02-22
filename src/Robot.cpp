#include <iostream>
#include <memory>

#include <IterativeRobot.h>
#include <LiveWindow/LiveWindow.h>

#include <CANTalon.h>
#include <WPILib.h>
#include <vector>

class SmoothController : public XboxController {
	//quadratic curve that makes full power around 80%, half power around 35%
	double c = 0.2;
	double b = 0.6;
	double a = 0.0; //this should remain at 0 so that 0 is always 0
	double GetSmoothed(double x) {
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
	frc::Timer autoTimer;
	std::vector<double> timeMark = {0, 0.2, 0.4, 0.6, 0.8, 1, 1.2, 1.4, 1.6, 1.8, 2, 2.2, 2.4, 2.6, 2.8, 3, 3.2, 3.4, 3.6, 3.8, 4, 4.2, 4.4, 4.6, 4.8, 5.0};
	std::vector<double> leftRPM = {0.0,2.439810925021615,3.6999321613816294,4.389744289512885,4.745912593981275,4.8984962692605425,4.916324664100744,4.832918856836043,4.6618385329473595,4.406708133179297,4.069185738276367,3.6569719501175215,3.1915875574782246,2.715484634203007,2.275551544247812,1.9084608356463555,1.6316117586644523,1.446186145330647,1.3409571068461048,1.3018852024357097,1.3173348131555354,1.3816386128862903,1.4920448109824973,1.64623266305009,1.834276685533078,2.040855072110574,2.2371756519279855,2.4046666704386612,2.53180056091191,2.6138408139833857,2.6488975061627658,2.6362546231191106,2.5751289131528523,2.4650524522072255,2.307299247991934,2.1080698116002896,1.8815595457885606,1.6535536512785334,1.4480901282680192,1.2819799238111962,1.1597491265273026,1.07684662612557,1.0218731042187623,0.9806604337210257,0.9370780769065099,0.8719473698536747,0.7584752577514011,0.5540658378140917};
	std::vector<double> rightRPM = {0.0,2.4517583408337846,3.7214908121334616,4.423805301491743,4.79724875318537,4.974292092954434,5.0269235624224615,4.992667803486761,4.890034736179607,4.727865799656778,4.512406226957782,4.250758676320649,3.955694210374224,3.6395624703666543,3.3313315646037003,3.0469956875110977,2.799100798710837,2.5939415733375313,2.4378758626637484,2.3341988198529755,2.2830812753492555,2.2796340130752433,2.3159910191956823,2.3812815200688666,2.4651924373654555,2.5550883077575457,2.6432811783616494,2.7212411345323724,2.7824137680356826,2.822343525404377,2.83842612855161,2.8290831523630375,2.7933280986999987,2.730510605115366,2.640929337642214,2.5254271120547305,2.3869804143068234,2.226845221523811,2.0578156771816043,1.8876966177450243,1.7242913215124038,1.571717871299919,1.4321900884973495,1.3035004082994284,1.1782039507837039,1.0411077966210367,0.8657951280218281,0.6074420815874603};
	double driveMultiplier = 1;
	double multiplier = 1;
	unsigned int currentTimeMark;
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
	SmoothController *driver;
	SmoothController* gunner;
    Compressor* compressor;
    DoubleSolenoid* solenoid;

	double SHOOTER_SHOOT = -3200.0, SHOOTER_IDLE = -SHOOTER_SHOOT / 10, INTAKE = 1000, RAMPRATE = 20; // TODO: Intake value is garbage

	void RobotInit() {
        std::cout << "Starting Robot Code! (612-2017 soda)" << std::endl;

		driver = new SmoothController(0);
		gunner = new SmoothController(1);

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

        compressor =  new Compressor(3);
        solenoid = new DoubleSolenoid(0, 1);
        solenoid->Set(DoubleSolenoid::Value::kForward);

        compressor->Start();
	}

	void AutonomousInit() {
		left1->SetTalonControlMode(CANTalon::TalonControlMode::kSpeedMode);
		left1->SetFeedbackDevice(CANTalon::FeedbackDevice::QuadEncoder);
		left1->SetPID(0.01, 0, 0, 0.5); 
		left1->SetVoltageRampRate(0);
		right1->SetTalonControlMode(CANTalon::TalonControlMode::kSpeedMode);
		right1->SetFeedbackDevice(CANTalon::FeedbackDevice::QuadEncoder);
		right1->SetPID(0.01, 0, 0, 0.5); 
		right1->SetVoltageRampRate(0);
        solenoid->Set(DoubleSolenoid::Value::kForward);
		currentTimeMark = 0;
		autoTimer.Reset();
		autoTimer.Start();
    }

    void AutonomousPeriodic() {
        left1->Set(leftRPM[currentTimeMark]*multiplier*driveMultiplier);
		left2->Set(left1->GetDeviceID());
		left3->Set(left1->GetDeviceID());
        right1->Set(rightRPM[currentTimeMark]*multiplier*driveMultiplier);
		right2->Set(right1->GetDeviceID());
		right3->Set(right1->GetDeviceID());
		while(currentTimeMark < timeMark.size() && timeMark[currentTimeMark+1]/multiplier < autoTimer.Get()) {
			currentTimeMark++;
		}
    }

	void TeleopInit() {
		left1->SetTalonControlMode(CANTalon::TalonControlMode::kThrottleMode);
		left1->SetVoltageRampRate(RAMPRATE);
		right1->SetTalonControlMode(CANTalon::TalonControlMode::kThrottleMode);
		right1->SetVoltageRampRate(RAMPRATE);
    }

    void DisabledInit() {
        intake1->SetSetpoint(0);
    }

	void TeleopPeriodic() {
		double a = driver->GetSmoothY(frc::GenericHID::kLeftHand);
		std::cout << "Left Y: " << a << std::endl;
		double b = driver->GetSmoothY(frc::GenericHID::kRightHand);
		std::cout << "Right Y: " << b << std::endl;
		//std::printf("%f, %f\n", a, b);
		//std::printf("%f, %f\n", abs(a), abs(b));

		if(a > 0.1f || a < -0.1f) {
			left1->Set(a);
		} else {
			left1->SetVoltageRampRate(0);
			left1->Set(0);
			left1->SetVoltageRampRate(RAMPRATE);
		}
		if(b > 0.1f || b < -0.1f) {
			right1->Set(-b);
		} else {
			right1->SetVoltageRampRate(0);
			right1->Set(0);
			right1->SetVoltageRampRate(RAMPRATE);
		}

		//std::printf("A: %d\n", gunner->GetAButton() ? 1 : 0);

		if(gunner->GetAButton())
			if(driver->GetStartButton())
				shooter1->SetSetpoint(SHOOTER_SHOOT * 1.25);
			else
				shooter1->SetSetpoint(SHOOTER_SHOOT);
		else
			shooter1->SetSetpoint(SHOOTER_IDLE);

		double c = gunner->GetSmoothTrigger(frc::GenericHID::kRightHand);
		//drivetrain blocking
		/*if(abs(a -b) > 1.4 && ((a > 0 && b < 0) || (a < 0 && b > 0)) && abs(c) > 0.1) {
            std::cout << "WARNING: Blocking drive train" << std::endl;
            left1->SetVoltageRampRate(0);
            left1->Set(0);
            left1->SetVoltageRampRate(RAMPRATE);

            right1->SetVoltageRampRate(0);
            right1->Set(0);
            right1->SetVoltageRampRate(RAMPRATE);
        }*/

		//std::printf("B: %d\n", gunner->GetBButton() ? 1 : 0);

		//Drivers seemed to like this
		std::cout << "Triggered: " << c << std::endl;
		if(abs(c) > 0.1) {
			if (gunner->GetBumper(frc::GenericHID::kLeftHand))
				intake1->SetSetpoint(-INTAKE); //allows us to clear intake
			else
				intake1->SetSetpoint(INTAKE);
		} else {
			intake1->SetSetpoint(0);
			std::cout << "Hi" << std::endl;
		}

		intake1->SetSetpoint(INTAKE);

		double d = gunner->GetSmoothY(frc::GenericHID::kLeftHand);

		if(d > 0.05f || d < -0.05f)
			climber1->Set(d);
		else
			climber1->Set(0);
		if(driver->GetBumper(frc::GenericHID::kLeftHand))
            solenoid->Set(DoubleSolenoid::Value::kForward);
        else if(driver->GetBumper(frc::GenericHID::kRightHand))
            solenoid->Set(DoubleSolenoid::Value::kReverse);
	}
};

START_ROBOT_CLASS(Robot)
