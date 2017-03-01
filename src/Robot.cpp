#include <iostream>
#include <memory>

#include <IterativeRobot.h>
#include <LiveWindow/LiveWindow.h>

#include <CANTalon.h>
#include <WPILib.h>
#include <fstream>
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

	frc::Timer* autoTimer;
	//std::vector<double> timeMark = {0, 0.5, 1, 4, 4.5};
	//std::vector<double> leftRPM = {50, 100, 200, 150, 0};
	//std::vector<double> rightRPM = {50, 100, 200, 150, 0};
	//double driveMultiplier = 2;
	double multiplier = 1;

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
	CANTalon* climber2;
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
		climber2 = new CANTalon(12);

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

		left2->SetTalonControlMode(CANTalon::TalonControlMode::kFollowerMode);
		left2->Set(left1->GetDeviceID());
		left3->SetTalonControlMode(CANTalon::TalonControlMode::kFollowerMode);
		left3->Set(left1->GetDeviceID());

		right1 = new CANTalon(6);
		right2 = new CANTalon(5);
		right3 = new CANTalon(4);

		right2->SetTalonControlMode(CANTalon::TalonControlMode::kFollowerMode);
		right2->Set(right1->GetDeviceID());
		right3->SetTalonControlMode(CANTalon::TalonControlMode::kFollowerMode);
		right3->Set(right1->GetDeviceID());

		compressor = new Compressor(3);
		solenoid = new DoubleSolenoid(0, 1);
		solenoid->Set(DoubleSolenoid::Value::kForward);

		climber2->SetTalonControlMode(CANTalon::TalonControlMode::kFollowerMode);
		climber2->Set(climber1->GetDeviceID());

		compressor->Start();

		autoTimer = new Timer();
	}

	void AutonomousInit() {
		autoTimer->Reset();
		autoTimer->Start();
		left1->SetTalonControlMode(CANTalon::TalonControlMode::kThrottleMode);
		right1->SetTalonControlMode(CANTalon::TalonControlMode::kThrottleMode);
		std::ifstream profile_reader;

		//load the profile of the correct mode
		std::string file = "/home/lvuser/";
		auto current_mode = frc::SmartDashboard::GetString("Chosen Autonomous Mode", "None");
		//make sure we do nothing if the auto mode is set to none
		if(current_mode == "None")
			return;

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
			return;
		}

		while(!profile_reader.is_open()) {
			std::cout << "Opening " << file << "..." << std::endl;
			profile_reader.open(file);
			frc::Wait(0.25);
		}
		std::vector<double> times = {0};
		std::vector<double> lefts = {0};
		std::vector<double> rights = {0};
		unsigned long colonPos = 0;
		unsigned long commaPos = 0;
		std::string timeString;
		std::string leftString;
		std::string rightString;
		std::string line;
		if(profile_reader.is_open()) {
			std::cout << "Reading motion profile" << std::endl;
			while(getline(profile_reader,line)) {
				colonPos = line.find(":");
				commaPos = line.find(",");
				timeString = line.substr(0, colonPos);
				leftString = line.substr(colonPos + 1, commaPos - colonPos - 1);
				rightString = line.substr(commaPos + 1);
				times.push_back(std::stod(timeString) / multiplier);
				lefts.push_back(std::stod(leftString) * multiplier);
				rights.push_back(std::stod(rightString) * multiplier);
			}
		}
		uint32_t t = 0;
		std::cout << "Running motion profile" << std::endl;
		times.pop_back();
		rights.pop_back();
		lefts.pop_back();
		while(t < times.size() && autoTimer->Get() < times.back()) {
			while(t < times.size() && times[t + 1] < autoTimer->Get()) {
				t++;
			}
			left1->Set(lefts[t]);
			right1->Set(lefts[t]);
			std::cout << times[t] << ":" << lefts[t] << "," << rights[t] << std::endl;
		}
		profile_reader.close();
	}

	void AutonomousPeriodic() {
		//leave blank?
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
        double forward = -driver->GetSmoothY(frc::GenericHID::kLeftHand);
        double rotation = -driver->GetSmoothX(frc::GenericHID::kRightHand);
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
		double a = left;
		std::cout << "Left Y: " << a << std::endl;
		double b = -right; //verify negative
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
			right1->Set(b);
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
			shooter1->SetSetpoint(0);

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

		double d = gunner->GetY(frc::GenericHID::kLeftHand);

		if(-d > 0.25f)
			climber1->Set(-1);
		else
			climber1->Set(0);
		if(driver->GetBumper(frc::GenericHID::kLeftHand))
			solenoid->Set(DoubleSolenoid::Value::kForward);
		else if(driver->GetBumper(frc::GenericHID::kRightHand))
			solenoid->Set(DoubleSolenoid::Value::kReverse);
	}
};

START_ROBOT_CLASS(Robot)
