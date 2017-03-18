#pragma once

#include <Commands/Command.h>

class AutoDriveEnc: public frc::Command {
public:
    AutoDriveEnc(float distance, float speed);
    void Initialize() override;
    void Execute() override;
    bool IsFinished() override;
    void End() override;
    void Interrupted() override;
private:
    float _distance; // Distance to drive (in encoder PPR)
    float _speed; // Speed to drive (-1.0f to 1.0f)
};
