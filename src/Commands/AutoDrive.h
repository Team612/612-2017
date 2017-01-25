#pragma once

#include <WPILib.h>
#include "RobotMap.h"

class AutoDrive: public Command {
public:
  AutoDrive(double time);
  void Initialize() override;
  void Execute() override;
  bool IsFinished() override;
  void End() override;
  void Interrupted() override;
private:
};
