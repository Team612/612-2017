#include "Gear.h"
#include "Commands/AlignToTarget.h"
#include "Commands/DriveDistance.h"
#include "Commands/DriveDistance.h"

Gear::Gear() {
     // Add Commands here:
    // e.g. AddSequential(new Command1());
    //      AddSequential(new Command2());
    // these will run in order.

    // To run multiple commands at the same time,
    // use AddParallel()
    // e.g. AddParallel(new Command1());
    //      AddSequential(new Command2());
    // Command1 and Command2 will run in parallel.

    // A command group will require all of the subsystems that each member
    // would require.
        AddSequential(new AlignToTarget());
        AddSequential(new DriveDistance(0));
        AddSequential(new DriveDistance(0));
 }
