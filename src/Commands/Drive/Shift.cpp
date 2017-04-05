#include "Shift.h"
#include "../../Robot.h"

Shift::Shift(SHIFT_DIR dir) {
  this->dir = dir;
  Requires(Robot::drivetrain.get());
  SetTimeout(.5);
}

void Shift::Initialize() {

}

void Shift::Execute() {
    Robot::drivetrain->ThrottleByRPM(0, 0);
    if(TimeSinceInitialized() <= .25){
    if(dir == UP)
        Robot::shifter->ShiftUp();
    else if(dir == DOWN)
        Robot::shifter->ShiftDown();
    else if(dir == OFF)
        Robot::shifter->ShiftOff();
    else
        std::cout << "why is the shifter not working?(Shift.cpp:" << __LINE__ << ") \n";
    }
}

bool Shift::IsFinished() {
    return IsTimedOut();
}

void Shift::End() {

}

void Shift::Interrupted() {

}
