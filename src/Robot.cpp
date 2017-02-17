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
    CANTalon* climber2;
    XboxController* driver;
    XboxController* gunner;
    Servo* servo;

    double SHOOTER_SHOOT = 3200.0, SHOOTER_IDLE = -SHOOTER_SHOOT / 5, INTAKE = 1000; // TODO: Intake value is garbage

    void RobotInit() {
        driver = new XboxController(0);
        gunner = new XboxController(1);

        shooter1 = new CANTalon(1);
        shooter2 = new CANTalon(2);
        intake1 = new CANTalon(4);
        climber1 = new CANTalon(6);
        climber1->SetInverted(true);
        climber2 = new CANTalon(7);
        intake2 = new CANTalon(3);

        servo = new Servo(0);

        shooter1->SetInverted(false);
        shooter1->SelectProfileSlot(0);
        shooter1->SetPID(0.1, 0.001, 4.1, 0.026);
        shooter1->SetFeedbackDevice(CANTalon::FeedbackDevice::CtreMagEncoder_Relative);
        shooter1->SetTalonControlMode(CANTalon::TalonControlMode::kSpeedMode);
        shooter1->SetSensorDirection(false);
        shooter1->ConfigNominalOutputVoltage(+0.0f, -0.0f);
        shooter1->ConfigPeakOutputVoltage(+12.0f, -12.0f);


        shooter2->SetControlMode(CANSpeedController::ControlMode::kFollower);
        shooter2->Set(1); // SAME AS ID FOR SHOOTER 1

        intake1->SelectProfileSlot(0);
        intake1->SetPID(0.12, 0.001, 5, 0.08);
        intake1->SetFeedbackDevice(CANTalon::FeedbackDevice::CtreMagEncoder_Relative);
        intake1->SetTalonControlMode(CANTalon::TalonControlMode::kSpeedMode);
        intake1->SetSensorDirection(false);
        intake1->ConfigNominalOutputVoltage(+0.0f, -0.0f);
        intake1->ConfigPeakOutputVoltage(+12.0f, -12.0f);

        intake2->SetControlMode(CANSpeedController::ControlMode::kFollower);
        intake2->Set(4); // SAME AS ID FOR INTAKE 1

//		left1 = new CANTalon(1);
//		left2 = new CANTalon(2);
//		left3 = new CANTalon(3);
//		left1->SetControlMode(CANSpeedController::ControlMode::kPercentVbus);
//		left1->SetInverted(true);
//		//left1->SetInverted(true);
//		//left1->SetInverted(true);
//
//		left2->SetControlMode(CANSpeedController::ControlMode::kFollower);
//		left2->Set(1); // SAME AS ID FOR LEFT 1
//		left3->SetControlMode(CANSpeedController::ControlMode::kFollower);
//		left3->Set(1); // SAME AS ID FOR LEFT 1
//
//		right1 = new CANTalon(23);//4
//		right2 = new CANTalon(7);//7
//		right3 = new CANTalon(6);//6
//		right1->SetControlMode(CANSpeedController::ControlMode::kPercentVbus);
//		right1->SetInverted(true);
//
//
//		right2->SetControlMode(CANSpeedController::ControlMode::kFollower);
//		right2->Set(23); // SAME AS ID FOR RIGHT 1
//		right3->SetControlMode(CANSpeedController::ControlMode::kFollower);
//		right3->Set(23); // SAME AS ID FOR RIGHT 1
    }

    void AutonomousInit() override {}
    void AutonomousPeriodic() {}

    void TeleopInit() {

    }


    void TeleopPeriodic() {
//		double a = driver->GetY(frc::GenericHID::kLeftHand);
//		double b = driver->GetY(frc::GenericHID::kRightHand);
//		//std::printf("%f, %f\n", a, b);
//		//std::printf("%f, %f\n", abs(a), abs(b));
//			if(a > 0.1f || a < -0.1f){
//				left1->Set(a);
//
//			}
//			else{
//				left1->Set(0);
//
//			}
//			if(b > 0.1f || b < -0.1f){
//				right1->Set(b);
//
//				}
//			else{
//				right1->Set(0);
//			}
//		std::printf("%d\n", gunner->GetAButton() ? 1 : 0);
//
////		int multiplier = gunner->GetBButton() ? -1 : 1
        //int multiplier = 1;
        std::cout << -gunner->GetY(frc::GenericHID::kLeftHand) << std::endl;
        if(-gunner->GetY(frc::GenericHID::kLeftHand) > 0.1)
            shooter1->SetSetpoint(SHOOTER_SHOOT);
        else
            shooter1->SetSetpoint(SHOOTER_IDLE);

        //std::printf("%d\n", gunner->GetBButton() ? 1 : 0);
        if(gunner->GetBButton())
            intake1->SetSetpoint(INTAKE);
        else if(gunner->GetAButton())
            intake1->SetSetpoint(-INTAKE / 3);
        else
            intake1->Set(0);
        climber1->Set(gunner->GetXButton() ? 1.0f : (gunner->GetYButton() ? 0.2f : 0));
        //climber2->Set(gunner->GetXButton() ? 1.0f : (gunner->GetYButton() ? 0.2f : 0));
        servo->Set(gunner->GetBumper(frc::GenericHID::kLeftHand) ? 1.0f : 0);
    }
};

START_ROBOT_CLASS(Robot)

/*
 * Controls:
 * Gunner - X: full climb, Y: partial climb, Left bumper: grab, Right Bumper: Auto Align, Left Stick Y: Shoot, B: intake, A: slow outtake
 * Driver - Tank Drive
 */
