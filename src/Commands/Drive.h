#pragma once

#include "Commands/Command.h"

class Drive: public Command {
public:
	Drive();

	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();

private:

};
