#pragma once
#include "../../Robot.h"
#include <WPILib.h>
#include "RobotMap.h"
#include "CANTalon.h"

enum class TalonENUM {SHOOTER, FL, FR, RL, RR};

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
    //float timer;
};
