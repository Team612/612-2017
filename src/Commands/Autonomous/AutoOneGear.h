#pragma once

#include "Commands/PIDCommand.h"
#include <WPILib.h>
#include "RobotMap.h"

class AutoOneGear: public PIDCommand {
public:
  AutoOneGear();
  void Initialize() override;
  void Execute() override;
  bool IsFinished() override;
  void End() override;
  void Interrupted() override;
  double ReturnPIDInput();
  void UsePIDOutput(double output);
private:
  double pi = 3.141592653;

  double DISTANCE_METERS = -5;
  double DISTANCE; //Encoder units
  double leftInitialDistance;
  double rightInitialDistance;
};
