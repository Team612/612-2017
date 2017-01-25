#pragma once

#include "Commands/Command.h"
#include <WPILib.h>
#include "RobotMap.h"

class AutoDrive: public Command {
public:
  AutoDrive(float time, float speed);
  void Initialize() override;
  void Execute() override;
  bool IsFinished() override;
  void End() override;
  void Interrupted() override;
private:
  float myTime;
  float mySpeed;
};
