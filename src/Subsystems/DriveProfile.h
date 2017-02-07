#pragma once

class DriveProfile {
/*
Not to be confused with a motion profile
Drive profile is all the different dimensions on the robot
*/
public:
    DriveProfile();
    DriveProfile(double ntr, double etw, double wd, double ww, double wmr, bool te, int lte, int rte);
    DriveProfile(double ntr, double etw, double wd, double ww, double wmr, bool te, int lte, int rte, double f, double p, double i, double d);
    double NativeToRPM;          //encoder native units per 100ms * NativeToRPM = encoder RPM
    double EncoderToWheel;       //encoder RPM * EncoderToWheel = wheel rpm
    double WheelDiameter;        //wheel diameter in meters
    double WheelWidth;           //width of the robot (distance from left side to right side in meters)
    double WheelFriction = 1.0;  //wheel tangential velocity * WheelFriction = linear velocity (0.0 to 1.0, use 1.0 as default)
    double WheelMaxRPM;          //The max RPM of the wheels
    bool TwoEncoder;             //if true, use two encoders (LeftTalonEncoder and RightTalonEncoder) instead of all four
    int LeftTalonEncoder = 0;    //0 = drive_fl, 1 = drive_rl (TwoEncoder must be true)
    int RightTalonEncoder = 0;   //0 = drive_fr, 1 = drive_rr (TwoEncoder must be true)
    double F;                    //FeedFoward gain (native units)
    double P;                    //Proportional gain
    double I;                    //Integral gain
    double D;                    //Derivative gain
};
