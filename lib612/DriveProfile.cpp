#include "DriveProfile.h"

DriveProfile::DriveProfile() {

}

DriveProfile::DriveProfile(double ntr, double etw, double wd, double ww, double wf, double wmr, bool te, int lte, int rte) {
    NativeToRPM = ntr;
    EncoderToWheel = etw;
    WheelDiameter = wd;
    WheelWidth = ww;
    WheelFriction = wf;
    WheelMaxRPM = wmr;
    TwoEncoder = te;
    LeftTalonEncoder = lte;
    RightTalonEncoder = rte;
}

DriveProfile::DriveProfile(double ntr, double etw, double wd, double ww, double wf, double wmr, bool te, int lte, int rte, double f, double p, double i, double d) {
    NativeToRPM = ntr;
    EncoderToWheel = etw;
    WheelDiameter = wd;
    WheelWidth = ww;
    WheelFriction = wf;
    WheelMaxRPM = wmr;
    TwoEncoder = te;
    LeftTalonEncoder = lte;
    RightTalonEncoder = rte;
    F = f;
    P = p;
    I = i;
    D = d;
}
