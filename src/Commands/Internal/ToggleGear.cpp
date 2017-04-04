#include "Robot.h"
#include "ToggleGear.h"

ToggleGear::ToggleGear(GearState set_state) : Command("ToggleGear") {
    state = set_state;
    Requires(Robot::gear_system.get());
}

void ToggleGear::Initialize() {
    switch(state) {
        case GearState::OPEN:
            Robot::gear_system->GearOpen();
            break;
        case GearState::CLOSED:
            Robot::gear_system->GearClose();
            break;
    }

}


bool ToggleGear::IsFinished() {
    return true;
}
