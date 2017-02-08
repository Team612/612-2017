#include "Commands/Autonomous/TenBallAuto.h"

TenBallAuto::TenBallAuto() {

    AddSequential(new DriveDistance(1.5));
    AddSequential(new AlignToTarget());
    AddSequential(new AutoShoot());

}
