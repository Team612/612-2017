#include "SolenoidShift.h"

#include "../../Robot.h"

SolenoidUp::SolenoidUp(int Shifter) : Command("SolenoidShift") {
Requires(Robot::shiftHopper.get());
this->UpDown = Shifter;
}

void SolenoidUp::Initialize() {
}

void SolenoidUp::Execute() {
  if(UpDown == 0){
    Robot::shiftHopper->ShiftUp();
  }
  if(UpDown == 1){
    Robot::shiftHopper->ShiftDown();
  }
}

bool SolenoidUp::IsFinished() {
    return true;
}

void SolenoidUp::End() { }

void SolenoidUp::Interrupted() { }
