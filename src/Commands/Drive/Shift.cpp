#include "Shift.h"
#include "../../Robot.h"

Shift::Shift(SHIFT_DIR dir) {
    this->dir = dir;
}

void Shift::Initialize() {

}

void Shift::Execute() {
    if(dir == UP)
        Robot::shifter_subsys->ShiftUp();
    else if(dir == DOWN)
        Robot::shifter_subsys->ShiftDown();
    else if(dir == OFF)
        Robot::shifter_subsys->ShiftOff();
    else
        std::cout << "God has made a mistake giving humanity intelligence, we do not know how to use it. (Shift.cpp:" << __LINE__ << ") \n";
}

bool Shift::IsFinished() {
    return false;
}

void Shift::End() {

}

void Shift::Interrupted() {

}
