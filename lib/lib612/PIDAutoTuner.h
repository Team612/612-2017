#pragma once
#include "SpeedController.h"
#include "PIDController.h"
#include <cmath>

namespace lib612{
    template <class FEEDBACK_DEVICE> //Device from which to get values for PID. Any PIDSource device works
    //In theory, all this really needs is a Get() method that returns a value
    //In practice, use WPILib-supported sentences unless you know what you are doing
    class PIDAutoTuner{
    private:
        enum TUNE_VAL {Kp, Ki, Kd, Kf};

        TUNE_VAL currentlyTuning;

        SpeedController& plant;
        FEEDBACK_DEVICE& source;

        double startingPStep = 0.01; //first step used for P that is provided by the user. Defaults to 0.01
        double startingIStep = 0.001; //first step used for I that is provided by the user. Defaults to 0.001
        double startingDStep = 0.01; //first step used for D that is provided by the user. Defaults to 0.01
        double startingFStep = 0.01; //first step used for F that is provided by the user. Defaults to 0.01
        double setPoint;

        double P = 0;
        double I = 0;
        double D = 0;
        double F = 0;

        double iZone;

        double acceptableDeviance = 0.5; //acceptable deviation from the setpoint by percentage
        double acceptableTimeToPoint = 5; //in seconds, the amount of time allowed to reach the Setpoint
        double acceptableInconsistency = .05; //max r value difference from 1 for data over 5 seconds after system reaches relative stablity.
        //compares the graph of y=setPoint to the actual dataset over 5 seconds.

        bool permissionP = true;
        bool permissionI = true;
        bool permissionD = true;
        bool permissionF = true;

        void tuneP(); //P Tuning Loop
        void tuneI(); //I Tuning Loop
        void tuneD(); //D Tuning Loop
        void tuneF(); //F Tuning Loop

        bool detectPTuned(); //detects if P is tuned (used internally), may just return DetectOscilation
        bool detectITuned(); //detects if I is tuned (used internally)
        bool detectDTuned(); //detects if D is tuned (used internally)
        bool detectFTuned(); //detects if F is tuned (used internally)
        bool detectLoopTuned(); //detects if the entire loop is tuned

        void modifyStep(double deltaStep);
        void Feed(double sensorValue);

        bool DetectOverwinding(); //Detects overwinding due to I accumulation
        bool DetectOscilation(); //Detects Oscilation over a period of x seconds.


    protected:

    public:
        PIDAutoTuner();
        PIDAutoTuner(SpeedController& plant, FEEDBACK_DEVICE& source);
        ~PIDAutoTuner();

        void SetStartingP(double p); //unimplemented
        void SetStartingI(double i); //unimplemented
        void SetStartingD(double d); //unimplemented
        void SetStartingF(double f); //unimplemented
        void SetStartingPIDF(double p, double i, double, double f); //unimplemented
        void SetStep(double step); //unimplemented

        void PermitTuningP(bool permission); //unimplemented
        void PermitTuningI(bool permission); //unimplemented
        void PermitTuningD(bool permission); //unimplemented
        void PermitTuningF(bool permission); //unimplemented
        void SetPermissions(bool permP = true, bool permI = true, bool permD = true, bool permF = true); //unimplemented

        void Start(double setPoint); //unimplemented
        //Tunes F, P, I and D in that order, skipping what was not permitted.
        //unimplemented beneath this point
        double GetFinalP(); //checks if the loop is finished, then returns P. If the loop is unfinished, it returns -1
        double GetFinalI(); //checks if the loop is finsihed, then returns I. If the loop is unfinished, it returns -1
        double GetFinalD(); //checks if the loop is finsihed, then returns D. If the loop is unfinished, it returns -1
        double GetFinalF(); //checks if the loop is finsihed, then returns F. If the loop is unfinished, it returns -1
        double GetFinalIZone(); //checks if loop is finished, then returns a recommended izone value

  };
}
