#include "SolenoidShift.h"

#include "../../Robot.h"

SolenoidShift::SolenoidShift(int Shifter) : Command("SolenoidShift") {
Requires(Robot::shiftHopper.get());
this->UpDown = Shifter;
}

void SolenoidShift::Initialize() {
}

void SolenoidShift::Execute() {
  if(SolenoidShift::UpDown == 0){
    Robot::shiftHopper->ShiftUp();
  }
  if(SolenoidShift::UpDown == 1){
    Robot::shiftHopper->ShiftDown();
  }
}

bool SolenoidShift::IsFinished() {
    return true;
}

void SolenoidShift::End() { }

void SolenoidShift::Interrupted() { }
