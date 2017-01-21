


#pragma once

#include "Commands/Command.h"


/**
 *
 *
 * @author ExampleAuthor
 */
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
