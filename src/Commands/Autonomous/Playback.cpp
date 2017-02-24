#include "Playback.h"
#include "../../RobotMap.h"
#include "../../Robot.h"

Playback::Playback(std::vector<double> time_mark, std::vector<double> left_setpoints, std::vector<double> right_setpoints, bool is_inverted)
        : Command("Playback") {
    this->time_mark = time_mark;
    this->left_setpoints = left_setpoints;
    this->right_setpoints = right_setpoints;
    this->is_inverted = is_inverted;
    timer = new Timer();
    Requires(Robot::drivetrain.get());
}

void Playback::Initialize() {
    if(is_inverted) {
        //run the play back with left as right and right as left
    } else {
        //run the play back normally
    }
}

void Playback::Execute() {
    //this should remain empty
}

bool Playback::IsFinished() {
    //only runs once
    //TODO consider using an instant command?
    return true;
}

void Playback::End() {
    Robot::drivetrain->Throttle(0, 0);
}

void Playback::Interrupted() {
    std::cout << "Warning: Driver playback interrupted!" << std::endl;
    Robot::drivetrain->Throttle(0, 0);
}
