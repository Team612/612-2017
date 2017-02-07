#include "Commands/Autonomous/TenBallAuto.h"

TenBallAuto::TenBallAuto() {
AddSequential(new DriveDistance(5.0));
// 4 feet 4 in
}
