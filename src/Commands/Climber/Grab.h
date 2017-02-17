#pragma once

#include "Commands/InstantCommand.h"

class Grab : public InstantCommand {
public:
    Grab();
    virtual void Execute() override;
    virtual void End() override;
};

