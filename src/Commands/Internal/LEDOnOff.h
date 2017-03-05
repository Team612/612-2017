#pragma once

#include "WPILib.h"

class LEDOnOff: public Command {

public:
    LEDOnOff();

    void Initialize() override;
    void Execute() override;
    bool IsFinished() override;
    void End() override;
    void Interrupted() override;
};
