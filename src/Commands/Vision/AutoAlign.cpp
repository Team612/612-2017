#include "AutoAlign.h"

AutoAlign::AutoAlign(HorizontalFind::Direction dir) {
	AddSequential(new HorizontalFind(dir));
	AddSequential(new HorizontalAlign(5));
	//AddSequential(new MoveToTarget(20));
}
