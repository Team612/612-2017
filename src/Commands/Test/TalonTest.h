#pragma once
#include "../../Robot.h"
#include <WPILib.h>
#include "RobotMap.h"
#include "CANTalon.h"
#include <stdio.h>

enum class TalonENUM {SHOOTER_L, SHOOTER_R, FL, FR, MR, ML, RL, RR, CLIMBER, INTAKE_L, INTAKE_R};

class TalonTest: public Command {
public:

  TalonTest(float timer, float speed, TalonENUM t);
  void Initialize() override;
  void Execute() override;
  bool IsFinished() override;
  void End() override;
  void Interrupted() override;
private:
    float speed;
    TalonENUM position;
    std::shared_ptr<CANTalon> chosen;
    CANTalon::TalonControlMode OriginalControlMode;
    std::shared_ptr<TalonSRX> chosenSRX;
    //float timer;
};
