#ifndef MoveToTarget_H
#define MoveToTarget_H

#include <WPILib.h>
#include <Robot.h>

class MoveToTarget : public PIDCommand {
public:
	MoveToTarget(int dist);
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();

	double ReturnPIDInput();
	void UsePIDOutput(double output);
	double current_power;

private:
	//Ultrasonic ur;
	int dist;
	double MIN_OUTPUT = 0.22;
};

#endif  // MoveToTarget_H
