#pragma once

#include "WPILib.h"
#include "Commands/Command.h"
#include "../../RobotMap.h"

class Shifter: public Command {
public:
  Shifter();
  void Initialize() override;
  void Execute() override;
  bool IsFinished() override;
  void End() override;
  void Interrupted() override;
};
