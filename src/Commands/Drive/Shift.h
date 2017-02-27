#pragma once

#include "WPILib.h"
#include "Commands/Command.h"
#include "../../RobotMap.h"

class Shift: public Command {
public:
  enum SHIFT_DIR {UP, DOWN, OFF};

  SHIFT_DIR dir;

  Shift(SHIFT_DIR dir);
  void Initialize() override;
  void Execute() override;
  bool IsFinished() override;
  void End() override;
  void Interrupted() override;
private:
 
};
