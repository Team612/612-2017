#include "Autonomous.h"
#include "AutoDrive.h"

Autonomous::Autonomous() {
    auto autonomous = frc::SmartDashboard::GetString("Chosen Autonomous Mode", "");
    if(autonomous == "Simple") {
        AddSequential(new AutoDrive(100, 100)); //TODO: find real setpoints!
    } else if(autonomous == "1 Gear Auto") {

    } else if(autonomous == "10 Ball Auto") {

    } else if(autonomous == "Full Gear Auto") {

    } else if(autonomous == "The Polymath") {

    } else if(autonomous == "Operation: Hopper Hack") {

    } else if(autonomous == "60 Ball Madlad Autonomous") {

    } else if(autonomous == "G.O.A.T.") {

    } else {
        std::cout << "Error: Failed to choose autonomous mode!" << std::endl;
        std::cout << "Warning: Defaulting to simple auto" << std::endl;
        AddSequential(new AutoDrive(100, 100));
    }
}
