#pragma once

#include <vector>

struct MotionProfile {
/*
Not to be confused with a drive profile
MotionProfile stores target velocity for left and right at a specific time
*/
	std::vector<double> time;  //time from t=0 to spin up to left and right
	std::vector<double> left;  //velocity of left side (m/s)
	std::vector<double> right; //velocity of right side (m/s)
	//time.size() == left.size() == right.size() should be true
};
