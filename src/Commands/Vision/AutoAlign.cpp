#include "AutoAlign.h"
#include "Robot.cpp"
AutoAlign::AutoAlign(HorizontalFind::Direction dir) {
	if(Robot::oi->getdriver()->GetYButton()){
			//do nothing
	}
	else if(Robot::oi->getdriver()->GetSmoothY() < 0.1||Robot::oi->getdriver()->GetSmoothY() > 0.1|| Robot::oi->getdriver()->GetSmoothY() < 0.1 || Robot::oi->getdriver()->GetSmoothY() > 0.1){}
{
 // do nothing	
}

	else{
	AddSequential(new HorizontalFind(dir));
	AddSequential(new HorizontalAlign(5));
}
	//AddSequential(new MoveToTarget(20));
}
