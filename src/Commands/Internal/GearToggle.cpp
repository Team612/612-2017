#include "GearToggle.h"
GearToggle::GearToggle() {
    Requires(Robot::gear_system.get());
}

void GearToggle::Initialize() {

    switch(  Robot::gear_system->GetGearState()) {
        case GearState::OPEN:
            Robot::gear_system->GearClose();
            break;
        case GearState::CLOSED:
            Robot::gear_system->(GearOpen);
            break;

}
}

void GearToggle::Execute() {


}

bool GearToggle::IsFinished() {
    return false;
}

void GearToggle::End() {
}

void GearToggle::Interrupted() {
}
