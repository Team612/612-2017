#include "Robot.h"
#include "ToggleGear.h"

ToggleGear::ToggleGear() : Command("ToggleGear") {
    Requires(Robot::gear_system.get());
}

void ToggleGear::Initialize() {
    switch(Robot::gear_system->GetGearState()) {
        case GearState::OPEN:
            Robot::gear_system->GearClose();
            break;
        case GearState::CLOSED:
            Robot::gear_system->GearOpen();
            break;
    }
}

bool ToggleGear::IsFinished() {
    return true;
}
