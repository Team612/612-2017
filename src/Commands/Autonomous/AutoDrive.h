#pragma once

#include "Commands/Command.h"
#include <WPILib.h>
#include "RobotMap.h"

class AutoDrive: public Command {
public:
    AutoDrive(float time, float speed);
    void Initialize() override;
    void Execute() override;
    bool IsFinished() override;
    void End() override;
    void Interrupted() override;
private:
    float _time; //time to drive (seconds)
    float _speed; //speed to drive (-1.0f to 1.0f)
};
