#pragma once
#include "DriverStation.h"
#include "WPILib.h"

#include <vector>
#include <functional>

namespace lib612 {
    namespace Networking {
        static std::vector<std::function<void(void)>> update_functions = { };

        inline void AddFunction(std::function<void(void)> fn) {
            update_functions.push_back(fn);
        }

        enum class Mode {
            AUTONOMOUS,
            TELEOPERATED,
            TEST,
            NULLMODE
        };

        //Robot mode based only on the driverstation
        inline  Mode GetRobotMode() {
            if (frc::DriverStation::GetInstance().IsAutonomous())
                return Mode::AUTONOMOUS;
            else if (frc::DriverStation::GetInstance().IsTest())
                return Mode::TEST;
            else if (frc::DriverStation::GetInstance().IsOperatorControl())
                return Mode::TELEOPERATED;
            else
                return Mode::NULLMODE;
        }

        inline void UpdateAll() {
            frc::SmartDashboard::PutBoolean("Enabled", frc::DriverStation::GetInstance().IsEnabled());
            //switch cases for GetRobotMode//
            switch (GetRobotMode()) {
            case Mode::AUTONOMOUS:
                frc::SmartDashboard::PutString("Mode", "Autonomous");
                break;
            case Mode::TELEOPERATED:
                frc::SmartDashboard::PutString("Mode", "Teleoperated");
                break;
            case Mode::TEST:
                frc::SmartDashboard::PutString("Mode", "Test");
                break;
            default:
                std::cout << "There is fundamental disorder in the universe (Networking.h " << __LINE__ << ")\n";
            }
            frc::SmartDashboard::PutNumber("Location", frc::DriverStation::GetInstance().GetLocation());
            frc::SmartDashboard::PutNumber("Match Time", frc::DriverStation::GetInstance().GetMatchTime());
            frc::SmartDashboard::PutNumber("Battery", frc::DriverStation::GetInstance().GetBatteryVoltage());

            for (auto function : update_functions) {
                //std::cout << "SD update" << std::endl;
                function();
            }
        }
    }
}
