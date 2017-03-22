#include "WPILib.h"
#include "CANTalon.h"
#include "lib612/SmoothController.h"

#define MAX_RPM 800

namespace PORTS {
    const uint32_t drive_talonFL = 1;
    const uint32_t drive_talonML = 3; // 3
    const uint32_t drive_talonRL = 2; // 2
    const uint32_t drive_talonFR = 4;
    const uint32_t drive_talonMR = 6;
    const uint32_t drive_talonRR = 5; // 5
}

class Robot : public IterativeRobot {
    CANTalon fl { PORTS::drive_talonFL };
    CANTalon ml { PORTS::drive_talonML };
    CANTalon rl { PORTS::drive_talonRL };
    CANTalon fr { PORTS::drive_talonFR };
    CANTalon mr { PORTS::drive_talonMR };
    CANTalon rr { PORTS::drive_talonRR };
    lib612::SmoothController controller  { 0 };
public:
    Robot() { }

    void RobotInit() override {
        std::cout << "Starting consistency test" << std::endl;
        ml.SetFeedbackDevice(CANTalon::FeedbackDevice::CtreMagEncoder_Relative);
        ml.ConfigNominalOutputVoltage(+0.0, -0.0);
        ml.ConfigPeakOutputVoltage(12.0, -12.0);
        ml.SelectProfileSlot(0);
        mr.SetFeedbackDevice(CANTalon::FeedbackDevice::CtreMagEncoder_Relative);
        mr.ConfigNominalOutputVoltage(+0.0, -0.0);
        mr.ConfigPeakOutputVoltage(12.0, -12.0);
        mr.SelectProfileSlot(0);
        frc::SmartDashboard::PutBoolean("Speed Mode", false);

        //left follow
        fl.SetTalonControlMode(CANTalon::TalonControlMode::kFollowerMode);
        rl.SetTalonControlMode(CANTalon::TalonControlMode::kFollowerMode);
        //right follow
        fr.SetTalonControlMode(CANTalon::TalonControlMode::kFollowerMode);
        rr.SetTalonControlMode(CANTalon::TalonControlMode::kFollowerMode);
    }

    void TeleopInit() override {
        if(frc::SmartDashboard::GetBoolean("Speed Mode", false)) {
            ml.SetTalonControlMode(CANTalon::TalonControlMode::kSpeedMode);
            mr.SetTalonControlMode(CANTalon::TalonControlMode::kSpeedMode);
        } else {
            ml.SetTalonControlMode(CANTalon::TalonControlMode::kThrottleMode);
            mr.SetTalonControlMode(CANTalon::TalonControlMode::kThrottleMode);
        }
    }

    void TeleopPeriodic() override {
        if(frc::SmartDashboard::GetBoolean("Speed Mode", false)) {
            ml.SetSetpoint(controller.GetY(frc::GenericHID::kLeftHand) * MAX_RPM);
            mr.SetSetpoint(controller.GetY(frc::GenericHID::kLeftHand) * MAX_RPM);
        } else {
            ml.Set(controller.GetY(frc::GenericHID::kLeftHand));
            mr.Set(controller.GetY(frc::GenericHID::kLeftHand));
        }
        fl.Set(ml.GetDeviceID());
        rl.Set(ml.GetDeviceID());
        fr.Set(mr.GetDeviceID());
        rr.Set(mr.GetDeviceID());

        frc::SmartDashboard::PutNumber("Left Side Speed", ml.GetSpeed());
        frc::SmartDashboard::PutNumber("Right Side Speed", mr.GetSpeed());
    };
};

START_ROBOT_CLASS(Robot)
