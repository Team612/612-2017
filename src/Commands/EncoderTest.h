#pragma once

#include <WPILib.h>
#include "RobotMap.h"

enum class Encode {L, R};

class EncoderTest: public Command {
public:

  EncoderTest(float timer, Encode e);
  void Initialize() override;
  void Execute() override;
  bool IsFinished() override;
  void End() override;
  void Interrupted() override;
private:
  Encode difEncoder;
};
