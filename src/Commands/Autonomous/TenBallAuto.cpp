#include "Commands/Autonomous/OneGearAuto.h"

OneGearAuto::OneGearAuto() {

    AddSequential(new DriveDistance(1.5));
    AddSequential(new AlignToTarget());
    AddSequential(new Shoot());
    
}
