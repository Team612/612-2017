#pragma once

#include "Commands/Command.h"
#include "../Robot.h"

class Climb: public Command {
public:
	Climb();

	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
private:

};
