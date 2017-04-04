#pragma once

#include "WPILib.h"
#include "Commands/Command.h"
#include "../../Robot.h"

class GearToggle: public Command {
public:
    GearToggle();
    void Initialize() override;
    void Execute() override;
    bool IsFinished() override;
    void End() override;
    void Interrupted() override;
};
/*
void GearToggle(){
  switch(  Robot::gear_system->GetGearState()) {
      case GearState::OPEN:
          Robot::gear_system->GearClose();
          break;
      case GearState::CLOSED:
          Robot::gear_system->(GearOpen);
          break;
  }

}*/
