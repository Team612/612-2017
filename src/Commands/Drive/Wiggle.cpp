#include "Wiggle.h"

Wiggle::Wiggle(Direction dir, double rate, double wiggle_time, double speed) {
    this->dir = dir;
    this->rate = rate;
    this->time = wiggle_time; //this odd syntax is because atom makes time a weird color. What is 'time' in c++?
    this->speed = speed;

    num_of_wiggles_to_do = wiggle_time/rate; //number of wiggles to do
    wiggle_every_n_sec = 1/rate; //how many seconds before changing direction of wiggle_time
    time_of_next_wiggle = 0;
    SetTimeout(wiggle_time);
    //WIGGLE WIGGLE WIGGLE YEAH
}

void Wiggle::Initialize() {
    if(dir == LEFT){
        Robot::drivetrain->SetVelocity(speed, -speed);
        wiggles_completed++;
        time_of_next_wiggle+=wiggle_every_n_sec;
    }else if(dir == RIGHT){
        Robot::drivetrain->SetVelocity(-speed, speed);
        wiggles_completed++;
        time_of_next_wiggle+=wiggle_every_n_sec;
    }else{
        std::cout << "Oh God, why? \n";
    }
}

void Wiggle::Execute() {
    time_spent_wiggling+=TimeSinceInitialized();
    if(TimeSinceInitialized() < time_of_next_wiggle){
        if(wiggle_next == LEFT){
            Robot::drivetrain->SetVelocity(speed, -speed);
        }else if(wiggle_next == RIGHT){
            Robot::drivetrain->SetVelocity(-speed, speed);
        }
    }else if(TimeSinceInitialized() >= time_of_next_wiggle){
        if(wiggle_next == LEFT){
            wiggle_next=RIGHT;
            wiggles_completed++;
        }else if(wiggle_next == RIGHT){
            wiggle_next=LEFT;
            wiggles_completed++;
        }
    }
}

bool Wiggle::IsFinished() {
    return IsTimedOut();
}

void Wiggle::End() {

}

void Wiggle::Interrupted() {

}
