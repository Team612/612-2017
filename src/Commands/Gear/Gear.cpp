#include "Gear.h"
#include "../Vision/AlignToTarget.h"
#include "../Drive/DriveDistance.h"

Gear::Gear() {
    AddSequential(new AlignToTarget());
    AddSequential(new DriveDistance(0));
    AddSequential(new DriveDistance(0));
 }
