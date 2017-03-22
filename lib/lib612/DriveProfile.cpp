#include "DriveProfile.h"

namespace lib612 {
    DriveProfile::DriveProfile(double ntr, double etw, double wd, double ww, double wf, double wmr, double f, double p, double i, double d) {
        NativeToRPM = ntr;
        EncoderToWheel = etw;
        WheelDiameter = wd;
        WheelWidth = ww;
        WheelFriction = wf;
        WheelMaxRPM = wmr;
        F = f;
        P = p;
        I = i;
        D = d;
    }

    double DriveProfile::CalcMaxVelocity() {
        double pi = 3.141592653;
        WheelMaxVelocity = (WheelDiameter*pi)*(WheelMaxRPM/60);
        return WheelMaxVelocity;
    }

    double DriveProfile::CalcMaxAccel(double TimeToMax) {
        WheelMaxAcceleration = WheelMaxVelocity/TimeToMax;
        return WheelMaxAcceleration;
    }

    double DriveProfile::CalcMaxJerk(double TimeToMax) {
        WheelMaxJerk = WheelMaxAcceleration/TimeToMax;
        return WheelMaxJerk;
    }
}
