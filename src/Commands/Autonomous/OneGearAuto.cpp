#include "Commands/Autonomous/OneGearAuto.h"

OneGearAuto::OneGearAuto() {

AddSequential(new AlignToTarget() );
AddSequential(new DriveDistance(3.0)); // needs to be 9 feet and 4 in 
AddSequential(new DriveDistance(-3.0)); // THE NUMBERS ARE PLACE HOLDERS UNTILL WE GET REAL NUMBERS


}
