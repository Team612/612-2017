#include "Commands/Autonomous/OneGearAuto.h"

OneGearAuto::OneGearAuto() {

AddSequential(new AlignToTarget() );
AddSequential(new DriveDistance(1.5)); // THE NUMBERS ARE PLACE HOLDERS UNTILL WE GET REAL NUMBERS
AddSequential(new DriveDistance(-1.5)); // THE NUMBERS ARE PLACE HOLDERS UNTILL WE GET REAL NUMBERS


}
