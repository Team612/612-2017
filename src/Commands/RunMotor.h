#pragma once



#include "WPILib.h"

#include "Commands/Command.h"



class RunMotor: public Command {

public:

  RunMotor(float power);

  void Initialize() override;

  void Execute() override;

  bool IsFinished() override;

  void End() override;

  void Interrupted() override;

};
