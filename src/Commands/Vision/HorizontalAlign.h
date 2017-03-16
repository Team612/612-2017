#ifndef AlignToTarget_H
#define AlignToTarget_H

#include "Robot.h"
#include "WPILib.h"
#include "VisionTarget.h"
#include <cmath>

class HorizontalAlign: public PIDCommand //PID for rotation
{
public:
    HorizontalAlign(float timeout = 0, bool continuous = false);
    void Initialize();
    void Execute();
    bool IsFinished();
    void End();
    void Interrupted();

    double ReturnPIDInput();
    void UsePIDOutput(double output);

private:
    bool hasTarget = false; //If we are tracking a target
    bool aligned = false;
    bool PIDUserDisabled = true; //If the PID is disabled because it succeeded or because the code forced it off
    int onTargetCounter = 0;
    bool continuous;

    void FindTarget(); //Tries to fill the CurrentTarget variable
    const double TARGET_ASPECT = 1.66/1.00; //Aspect ratio of game-target (it's 1'8" x 1')
    const int SCREEN_CENTER_X = 320; //Center of the screen. This is the point to which we will rotate
                                     //using PID.
    const int PIXEL_TOLERANCE = 4;
    const double PERCENT_TOLERANCE = 0.1;
    const int TICK_TOLERANCE = 10;

    const double ROT_SPEED_CAP = 0.3;
    const double ROT_SPEED_MIN = 0.1;

    int lastTargetDir = -1;
    int lastCenter = 0;
};

#endif
