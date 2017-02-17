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
  double pi = 3.141592653;

  bool stage1; // Drive forward
  bool stage2; // Rotate counter-clockwise
  bool stage2FirstRun; // Configure PID for rotation
  bool stage3; // Shoot Balls
  bool stage3FirstRun; // Disable PID and start timeout

  double DISTANCE_METERS = 4.0;
  double ROTATE_RADIANS = pi;
  double DISTANCE; //Encoder native units - calculated in constructor from DISTANCE_METERS
  double ROTATE; //Also encoder native units - calculated in constructor
  double leftInitialDistance;
  double rightInitialDistance;
  double SHOOT_TIME = 10.0;
  double OPTIMAL_RPM = 7500; // Shooter
  double IDLE = 300; // Shooter
};
