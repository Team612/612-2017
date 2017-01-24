#pragma once

#include "Commands/Command.h"

class MPDrive: public Command {
public:
    MPDrive(int profile);

    virtual void Initialize();
    virtual void Execute();
    virtual bool IsFinished();
    virtual void End();
    virtual void Interrupted();

private:

};
