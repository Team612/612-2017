#pragma once

#include "Commands/PIDCommand.h"
#include <WPILib.h>
#include "RobotMap.h"

class AutoTenBall: public PIDCommand {
public:
  AutoTenBall();
  void Initialize() override;
  void Execute() override;
  bool IsFinished() override;
  void End() override;
  void Interrupted() override;
  double ReturnPIDInput();
  void UsePIDOutput(double output);
private:
  bool stage1;
  bool stage2;
  bool stage2FirstRun;
  bool stage3;
  bool finished;
  double DISTANCE;
  double leftInitialDistance;
  double rightInitialDistance;
};
