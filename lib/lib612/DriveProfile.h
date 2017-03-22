#pragma once

namespace lib612 {
    class DriveProfile {
    /*
    Not to be confused with a motion profile
    Drive profile is all the different dimensions on the robot
    */
    public:
        DriveProfile() = delete;
        //DriveProfile(double ntr, double etw, double wd, double ww, double wf, double wmr);
        DriveProfile(double ntr, double etw, double wd, double ww, double wf, double wmr, double f, double p, double i, double d);
        double CalcMaxVelocity();              //max velocity is calculated, returned, and stored in WheelMaxVelocity
        double CalcMaxAccel(double TimeToMax); //max acceleration is calculated, returned, and stored in WheelMaxAcceleration
        double CalcMaxJerk(double TimeToMax);  //max jerk is calculated, returned, and stored in WheelMaxJerk
        double NativeToRPM;          //encoder native units per 100ms * NativeToRPM = encoder RPM
        double EncoderToWheel;       //encoder RPM * EncoderToWheel = wheel rpm
        double WheelDiameter;        //wheel diameter in meters
        double WheelWidth;           //width of the robot (distance from left side to right side in meters)
        double WheelFriction = 1.0;  //wheel tangential velocity * WheelFriction = linear velocity (0.0 to 1.0, use 1.0 as default)
        double WheelMaxRPM;          //The max RPM of the wheels
        double WheelMaxVelocity = 0.0;     //The max wheel tangential velocity from max RPM
        double WheelMaxAcceleration = 0.0; //The max wheel acceleration (linear)
        double WheelMaxJerk = 0.0;         //The max change in acceleration (linear)
        double F;                    //FeedForward gain (native units)
        double P;                    //Proportional gain
        double I;                    //Integral gain
        double D;                    //Derivative gain
    };
}
