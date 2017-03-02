#include <iostream>
#include <memory>

#include <IterativeRobot.h>
#include <LiveWindow/LiveWindow.h>

#include <CANTalon.h>
#include <WPILib.h>
#include <vector>
#include <cmath>

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
        std::cout << "Starting Robot Code! (612-2017 templateREPLACEME)" << std::endl;

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
		std::cout << "Autonomous Init! (612-2017 templateREPLACEME)" << std::endl;
    }

    void AutonomousPeriodic() {
    	std::cout << "Autonomous Periodic! (612-2017 templateREPLACEME)" << std::endl;
    }

	void TeleopInit() {
		std::cout << "Teleop Init! (612-2017 templateREPLACEME)" << std::endl;

		left1->SetTalonControlMode(CANTalon::TalonControlMode::kThrottleMode);
		left1->SetVoltageRampRate(0);
		right1->SetTalonControlMode(CANTalon::TalonControlMode::kThrottleMode);
		right1->SetVoltageRampRate(0);
    }

	double smoothed = false;

    double mQuickStopAccumulator;
    const double kThrottleDeadband = 0.02;
    const double kWheelDeadband = 0.02;
    const double kTurnSensitivity = .7;

    double HandleDeadband(double val, double deadband) {
        	        return (std::abs(val) > std::abs(deadband)) ? val : 0.0;
    }

    double Limit(double val) {
    	return (std::abs(val) > 1) ? ((val > 0) ? 1 : -1) : 0;
    }

	void TeleopPeriodic() {
    	std::cout << "Teleop Periodic! (612-2017 templateREPLACEME)" << std::endl;

    	double a, b;
    	if(driver->GetBumper(frc::GenericHID::kLeftHand)) {
    		a = driver->GetSmoothY(frc::GenericHID::kLeftHand);
    		b = driver->GetSmoothX(frc::GenericHID::kRightHand);
    	}
    	else {
    		a = driver->GetY(frc::GenericHID::kLeftHand);
    		b = driver->GetX(frc::GenericHID::kRightHand);
    	}

    	/**
    	 * Helper class to implement "Cheesy Drive". "Cheesy Drive" simply means that
    	 * the "turning" stick controls the curvature of the robot's path rather than
    	 * its rate of heading change. This helps make the robot more controllable at
    	 * high speeds. Also handles the robot's quick turn functionality - "quick turn"
    	 * overrides constant-curvature turning for turn-in-place maneuvers.
    	 */

    	        double wheel = HandleDeadband(b, kWheelDeadband);
    	        double throttle = HandleDeadband(a, kThrottleDeadband);
    	        double isQuickTurn = driver->GetBumper(frc::GenericHID::JoystickHand::kLeftHand);

    	        double overPower;
    	        double angularPower;

    	        if (isQuickTurn) {
    	            if (std::abs(throttle) < 0.2) {
    	                double alpha = 0.1;
    	                mQuickStopAccumulator = (1 - alpha) * mQuickStopAccumulator + alpha * Limit(wheel) * 2;
    	            }
    	            overPower = 1.0;
    	            angularPower = wheel;
    	        } else {
    	            overPower = 0.0;
    	            angularPower = std::abs(throttle) * wheel * kTurnSensitivity - mQuickStopAccumulator;
    	            if (mQuickStopAccumulator > 1) {
    	                mQuickStopAccumulator -= 1;
    	            } else if (mQuickStopAccumulator < -1) {
    	                mQuickStopAccumulator += 1;
    	            } else {
    	                mQuickStopAccumulator = 0.0;
    	            }
    	        }

    	        double right = throttle - angularPower;
    	        double left = throttle + angularPower;
    	        if (left > 1.0) {
    	            right -= overPower * (left - 1.0);
    	            left = 1.0;
    	        } else if (right > 1.0) {
    	            left -= overPower * (right - 1.0);
    	            right = 1.0;
    	        } else if (left < -1.0) {
    	            right += overPower * (-1.0 - left);
    	            left = -1.0;
    	        } else if (right < -1.0) {
    	            left += overPower * (-1.0 - right);
    	            right = -1.0;
    	        }

    	        left1->Set(left);
    	        right1->Set(-right);

		if(driver->GetBumper(frc::GenericHID::kLeftHand))
            solenoid->Set(DoubleSolenoid::Value::kForward);
        else if(driver->GetBumper(frc::GenericHID::kRightHand))
            solenoid->Set(DoubleSolenoid::Value::kReverse);
	}

    void DisabledInit() {
    	std::cout << "Disabled Init! (612-2017 templateREPLACEME)" << std::endl;
    }
};

START_ROBOT_CLASS(Robot)
