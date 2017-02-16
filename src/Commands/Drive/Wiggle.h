#pragma once

#include "WPILib.h"
#include "../../Robot.h"
#include <cmath>
#include "Commands/Command.h"

class Wiggle: public Command {
    //I made a copious number of variables because I like the wiggles
    //Seriously, the command is designed around this meme
private:
    enum Direction {LEFT, RIGHT};
    Direction dir; //direction to focus wiggling in
    Direction wiggle_next; //used internally for wiggle switching
    double rate; //wiggles per second
    double time; //seconds of wiggling
    double speed; //meters per second (gotta add the word wiggle to this comment: WIGGLE)

    double num_of_wiggles_to_do;
    double wiggle_every_n_sec;
    double wiggles_completed;
    double time_spent_wiggling;
    double time_of_next_wiggle;

public:
    Wiggle(Direction dir, double rate = 2, double wiggle_time = 3, double speed = 5);
    void Initialize() override;
    void Execute() override;
    bool IsFinished() override;
    void End() override;
    void Interrupted() override;
};
