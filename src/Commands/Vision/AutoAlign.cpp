#include "AutoAlign.h"
#include "Robot.cpp"
AutoAlign::AutoAlign(HorizontalFind::Direction dir) {
	if(Robot::oi->getgunner()->GetYButton()){
			//do nothing
	}
	else{
	AddSequential(new HorizontalFind(dir));
	AddSequential(new HorizontalAlign(5));
}
	//AddSequential(new MoveToTarget(20));
}
