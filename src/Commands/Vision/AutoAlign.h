#pragma once

#include "HorizontalAlign.h"
#include "HorizontalFind.h"
#include "MoveToTarget.h"
#include "Commands/CommandGroup.h"
#include "WPILib.h"

class AutoAlign: public CommandGroup {
public:
    AutoAlign(HorizontalFind::Direction dir);
};

