


#ifndef DRIVEDISTANCE_H
#define DRIVEDISTANCE_H


#include "Commands/Subsystem.h"
#include "../Robot.h"

/**
 *
 *
 * @author ExampleAuthor
 */
class DriveDistance: public Command {
public:

	DriveDistance(double distance);



	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();

private:


    double m_distance;


};

#endif
