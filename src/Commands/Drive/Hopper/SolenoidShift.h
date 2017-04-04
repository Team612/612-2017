#pragma once

#include "WPILib.h"

class SolenoidShift: public Command {

public:
    SolenoidShift(int Shifter);

    void Initialize() override;
    void Execute() override;
    bool IsFinished() override;
    void End() override;
    void Interrupted() override;
private:
      int UpDown;
};
