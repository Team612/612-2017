#include "Gear.h"
#include "../Vision/HorizontalAlign.h"
#include "../Drive/DriveDistance.h"

Gear::Gear() {
    AddSequential(new HorizontalAlign());
    AddSequential(new DriveDistance(0));
    AddSequential(new DriveDistance(0));
 }
