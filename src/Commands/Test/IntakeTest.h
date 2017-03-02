#pragma once

#include <WPILib.h>

class IntakeTest: public Command {
public:
  IntakeTest();
  void Initialize() override;
  void Execute() override;
  bool IsFinished() override;
  void End() override;
  void Interrupted() override;
};
