#include "FollowMP.h"

FollowMP::FollowMP(lib612::MotionProfile* mp): Command() {
    profile = mp;
}

void FollowMP::Initialize() {
    Requires(Robot::drivetrain.get());
    currentTimeMark = 0;
    timer.Reset();
    timer.Start();
}

void FollowMP::Execute() {
    Robot::drivetrain->SetRPM(profile->leftRPM[currentTimeMark],profile->rightRPM[currentTimeMark]);
    while(currentTimeMark < profile->time.size() && profile->time[currentTimeMark+1] < timer.Get()) {
        currentTimeMark++;
    }
}

bool FollowMP::IsFinished() {
    return currentTimeMark >= profile->time.size();
}

void FollowMP::End() {

}

void FollowMP::Interrupted() {

}
