#include "SolenoidShift.h"

#include "../../../Robot.h"

SolenoidShift::SolenoidShift() : Command("SolenoidShift") {
    Requires(Robot::shiftHopper.get());
}

void SolenoidShift::Initialize() {
    switch(Robot::shiftHopper->GetFlapState()) {
        case FLAP_STATE::UP:
            Robot::shiftHopper->ShiftDown();
            break;
        case FLAP_STATE::DOWN:
            Robot::shiftHopper->ShiftUp();
            break;
    }
}

void SolenoidShift::Execute() {

}

bool SolenoidShift::IsFinished() {
    return true;
}

void SolenoidShift::End() { }

void SolenoidShift::Interrupted() { }
