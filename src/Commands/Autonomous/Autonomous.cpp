#include "Autonomous.h"
#include "AutoDrive.h"
#include "AutoTenBall.h"

Autonomous::Autonomous() {
    auto chosen_mode = frc::SmartDashboard::GetString("Chosen Autonomous Mode", "");
    std::cout << "Chosen Autonomous mode: " << chosen_mode << std::endl;
    //IMPORTANT: the mode is chosen when the command is created
    if(chosen_mode == "Simple") {
        AddSequential(new AutoDrive(auto_time, auto_speed));
    } else if(chosen_mode == "1 Gear Auto") {

    } else if(chosen_mode == "10 Ball Auto") {
        AddSequential(new AutoTenBall());
    } else if(chosen_mode == "Full Gear Auto") {

    } else if(chosen_mode == "The Polymath") {

    } else if(chosen_mode == "Operation: Hopper Hack") {

    } else if(chosen_mode == "60 Ball Madlad Autonomous") {

    } else if(chosen_mode == "G.O.A.T.") {

    } else {
        std::cout << "Error: Failed to choose autonomous mode!" << std::endl;
        std::cout << "Warning: Defaulting to simple auto" << std::endl;
        AddSequential(new AutoDrive(auto_time, auto_speed));
    }
}
