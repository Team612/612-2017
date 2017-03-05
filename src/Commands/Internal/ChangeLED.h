#pragma once

#include "WPILib.h"

class ChangeLED: public Command {

public:
    ChangeLED();

    void Initialize() override;
    void Execute() override;
    bool IsFinished() override;
    void End() override;
    void Interrupted() override;
};
