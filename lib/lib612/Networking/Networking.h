#pragma once
#include "DriverStation.h"
#include "SmartDashboard.h"

namespace lib612 {
    namespace Networking {
        enum class Mode {
            AUTONOMOUS,
            TELEOPERATED,
            TEST,
            NULLMODE
        };

        void UpdateAll() {
            frc::SmartDashboard::PutBoolean("Enabled", frc::DriverStation::GetInstance()->IsEnabled());
            //switch cases for GetRobotMode//
            switch (GetRobotMode()) {
            case AUTONOMOUS:
                frc::SmartDashboard::PutString("Mode", "Autonomous");
                break;
            case TELEOPERATED:
                frc::SmartDashboard::PutString("Mode", "Teleoperated");
                break;
            case TEST:
                frc::SmartDashboard::PutString("Mode", "Test");
                break;
            default:
                std::cout << "There is fundemental disorder in the universe (Networking.h " << __LINE__ << ")\n";
            }
            frc::SmartDashboard::PutNumber("Location", frc::DriverStation::GetInstance()->GetLocation());
            frc::SmartDashboard::PutNumber("Match Time", frc::DriverStation::GetInstance()->GetMatchTime());
            frc::SmartDashboard::PutNumber("Battery", frc::DriverStation::GetInstance()->GetBatteryVoltage());
        }

        Mode GetRobotMode() {
            if (frc::DriverStation::GetInstance()->IsAutonomous())
                return AUTONOMOUS;
            else if (frc::DriverStation::GetInstance()->IsTest())
                return TELEOPERATED;
            else if (frc::DriverStation::GetInstance()->IsOperatorControl())
                return TEST;
            else
                return NULLMODE;
        }
    }
}
