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
  bool stage1; // Drive forward
  bool stage2; // Rotate counter-clockwise
  bool stage2FirstRun; // Configure PID for rotation
  bool stage3; // Shoot Balls
  bool stage3FirstRun; // Disable PID and start timeout
  
  double DISTANCE; //Encoder native units
  double ROTATE; //Also encoder native units
  double leftInitialDistance;
  double rightInitialDistance;
  double SHOOT_TIME;
  double OPTIMAL_RPM; // Shooter
  double IDLE; // Shooter
};
