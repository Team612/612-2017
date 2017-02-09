#pragma once
#include "DriverStation.h"
#include "SmartDashboard.h"

namespace lib612 {
    namespace Networking {

      enum class Mode {
        AUTONOMOUS,
        TELEOPERATED,
        TEST
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
          //printf("There is fundemental disorder in the universe (Networking.h) \n", );
          std::cout << "There is fundemental disorder in the universe (Networking.h) \n";
        }
        frc::SmartDashboard::PutNumber("Location", frc::DriverStation::GetInstance()->GetLocation());
        frc::SmartDashboard::PutNumber("Match Time", frc::DriverStation::GetInstance()->GetMatchTime());
        frc::SmartDashboard::PutNumber("Battery Voltage", frc::DriverStation::GetInstance()->GetBatteryVoltage());

      }

      Mode GetRobotMode() {
        if (IsAutonomous()) {
          return AUTONOMOUS;
        }
        else if (IsTest()) {
          return TELEOPERATED;
        }
        else if (IsOperatorControl()) {
          return TEST;
        }
      }

      //bool 	IsEnabled () const override;
      //start of modes//
      //bool IsAutonomous () const override;
      //bool IsTest () const override;
      //bool IsOperatorControl () const override;
      //end of modes//
      //int GetLocation () const;
      //double GetMatchTime () const;
      //double GetBatteryVoltage () const;
    }
}
