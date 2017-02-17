#pragma once

#include "lib612/MotionProfile.h"
#include "Commands/Command.h"
#include "../../Robot.h"

class FollowMP: public Command {
public:
    FollowMP(lib612::MotionProfile* mp);
    
    int currentTimeMark;
    frc::Timer timer;
    lib612::MotionProfile* profile;
    virtual void Initialize();
    virtual void Execute();
    virtual bool IsFinished();
    virtual void End();
    virtual void Interrupted();
};
