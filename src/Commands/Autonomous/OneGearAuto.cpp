#include "Commands/Autonomous/OneGearAuto.h"

OneGearAuto::OneGearAuto() {

AddSequential(new AlignToTarget() );
AddSequential(new DriveDistance(3.0)); // THE NUMBERS ARE PLACE HOLDERS UNTILL WE GET REAL NUMBERS
AddSequential(new DriveDistance(3.0)); // THE NUMBERS ARE PLACE HOLDERS UNTILL WE GET REAL NUMBERS


}
