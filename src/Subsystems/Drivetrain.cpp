#include "Drivetrain.h"
#include "../Commands/Drive/Drive.h"
#include "lib612/Networking/Networking.h"
#include "../RobotMap.h"
#include "../Robot.h"

Drivetrain::Drivetrain(lib612::DriveProfile* dp) : Subsystem("Drivetrain") {
    std::cout << "Drive"
            "" << std::endl;
    //ur = RobotMap::ultrasonic;
    ur2 = RobotMap::new_ultrasonic;
    profile = dp;

    //Make sure we're using the actual talon objects and not making our out copies
    this->drive_mr.reset(RobotMap::drive_mr.get());
    this->drive_fr.reset(RobotMap::drive_fr.get());
    this->drive_rr.reset(RobotMap::drive_rr.get());
    this->drive_ml.reset(RobotMap::drive_ml.get());
    this->drive_fl.reset(RobotMap::drive_fl.get());
    this->drive_rl.reset(RobotMap::drive_rl.get());

    //check if null
    if(this->drive_mr == nullptr || this->drive_fr == nullptr || this->drive_rr == nullptr || this->drive_ml == nullptr || this->drive_fl == nullptr || this->drive_rl == nullptr)
        std::cout << "Yolo one of these are nullo lolololo" << std::endl;

    /*this->drive_ml->SetPID(profile->P, profile->I, profile->D, profile->F);
    this->drive_mr->SetPID(profile->P, profile->I, profile->D, profile->F);
    this->drive_ml->SetFeedbackDevice(CANTalon::FeedbackDevice::QuadEncoder);
    this->drive_mr->SetFeedbackDevice(CANTalon::FeedbackDevice::QuadEncoder);*/

    this->drive_ml->SetTalonControlMode(CANTalon::TalonControlMode::kThrottleMode);
    this->drive_mr->SetTalonControlMode(CANTalon::TalonControlMode::kThrottleMode);
    this->drive_fl->SetTalonControlMode(CANTalon::TalonControlMode::kFollowerMode);
    this->drive_fl->Set(drive_ml->GetDeviceID());
    this->drive_fr->SetTalonControlMode(CANTalon::TalonControlMode::kFollowerMode);
    this->drive_fr->Set(drive_mr->GetDeviceID());
    //this->drive_fr->SetClosedLoopOutputDirection(true);
    this->drive_rl->SetTalonControlMode(CANTalon::TalonControlMode::kFollowerMode);
    this->drive_rl->Set(drive_ml->GetDeviceID());
    this->drive_rr->SetTalonControlMode(CANTalon::TalonControlMode::kFollowerMode);
    this->drive_rr->Set(drive_mr->GetDeviceID());
    this->drive_ml->SetVoltageRampRate(RAMP_RATE);
    this->drive_mr->SetVoltageRampRate(RAMP_RATE);
    this->drive_ml->SetInverted(true);
    this->drive_mr->SetInverted(false);

    this->drive_mr->ConfigNeutralMode(CANTalon::NeutralMode::kNeutralMode_Brake);
    this->drive_fr->ConfigNeutralMode(CANTalon::NeutralMode::kNeutralMode_Brake);
    this->drive_rr->ConfigNeutralMode(CANTalon::NeutralMode::kNeutralMode_Brake);
    this->drive_ml->ConfigNeutralMode(CANTalon::NeutralMode::kNeutralMode_Brake);
    this->drive_fl->ConfigNeutralMode(CANTalon::NeutralMode::kNeutralMode_Brake);
    this->drive_rl->ConfigNeutralMode(CANTalon::NeutralMode::kNeutralMode_Brake);

    //TODO Test this current limit
    this->drive_ml->SetCurrentLimit(MAX_AMPS);
    this->drive_rl->SetCurrentLimit(MAX_AMPS);
    this->drive_fl->SetCurrentLimit(MAX_AMPS);
    this->drive_mr->SetCurrentLimit(MAX_AMPS);
    this->drive_fr->SetCurrentLimit(MAX_AMPS);
    this->drive_rr->SetCurrentLimit(MAX_AMPS);

    this->drive_ml->EnableCurrentLimit(true);
    this->drive_rl->EnableCurrentLimit(true);
    this->drive_fl->EnableCurrentLimit(true);
    this->drive_mr->EnableCurrentLimit(true);
    this->drive_fr->EnableCurrentLimit(true);
    this->drive_rr->EnableCurrentLimit(true);

    this->drive.reset(RobotMap::drive.get());

    //TODO: Are these being used?
    //SetDistancePerPulse()
    //double DistancePerWheelRotation = pi*profile->WheelDiameter;
    //double WheelRPMPerPulsePer100ms = profile->NativeToRPM * profile->EncoderToWheel;
    //double WheelRotationsPerPulse = WheelRPMPerPulsePer100ms * (60/0.1);
    //double DistancePerPulse = DistancePerWheelRotation * WheelRotationsPerPulse;

    //update Smart Dashboard
    lib612::Networking::update_functions.push_back([this](){
        frc::SmartDashboard::PutNumber("Drivetrain P",this->profile->P);
        frc::SmartDashboard::PutNumber("Drivetrain I",this->profile->I);
        frc::SmartDashboard::PutNumber("Drivetrain D", this->profile->D);
        frc::SmartDashboard::PutNumber("Drivetrain F", this->profile->F);
        //frc::SmartDashboard::PutNumber("Total Robot Current", RobotMap::pdp->GetTotalCurrent());
        //frc::SmartDashboard::PutNumber("Climber Current", RobotMap::pdp->GetCurrent(15));
        //frc::SmartDashboard::PutNumber("Ultrasonic Distance (mm)", ur->GetRangeMM());
        frc::SmartDashboard::PutNumber("New Ultrasonic Distance in inches by regression combination", ur2->GetDistanceInches());
    });
}

void Drivetrain::SetDriveProfile(lib612::DriveProfile& dp) {
    *profile = dp;
}

void Drivetrain::SetDriveProfile(lib612::DriveProfile* dp) {
    profile = dp;
}

void Drivetrain::SetVelocity(double l, double r) {
    double TargetLeft = (60*(l/profile->WheelFriction))/(profile->WheelDiameter*PI); //Converts l to left wheel rpm
    double TargetRight = (60*(r/profile->WheelFriction))/(profile->WheelDiameter*PI); //Converts r to right wheel rpm
    SetRPM(TargetLeft, TargetRight);
}

void Drivetrain::SetRPM(double l, double r) {
    double TargetLeft = l;
    double TargetRight = r;
    if(std::abs(TargetLeft) > profile->WheelMaxRPM) {
        TargetLeft = (std::abs(TargetLeft)/TargetLeft)*profile->WheelMaxRPM; //If TargetLeft is greater that WheelMaxRPM, Set TargetLeft to WheelMaxRPM with correct sign
    }
    if(std::abs(TargetRight) > profile->WheelMaxRPM) {
        TargetLeft = (std::abs(TargetRight)/TargetRight)*profile->WheelMaxRPM; //If TargetRight is greater that WheelMaxRPM, Set TargetRight to WheelMaxRPM with correct sign
    }

    drive_ml->SetSetpoint(TargetLeft/profile->NativeToRPM);
    drive_fl->Set(drive_ml->GetDeviceID());
    drive_rl->Set(drive_ml->GetDeviceID());
    drive_mr->SetSetpoint(TargetRight/profile->NativeToRPM);
    drive_fr->Set(drive_mr->GetDeviceID());
    drive_rr->Set(drive_mr->GetDeviceID());
}

lib612::DriveProfile* Drivetrain::GetCurrentProfile() {
    return profile;
}

double Drivetrain::GetLeftVelocity() {
    return drive_ml->GetSetpoint();
}

double Drivetrain::GetRightVelocity() {
    return drive_mr->GetSetpoint();
}

void Drivetrain::ThrottleByRPM(double lpercent, double rpercent) {
    SetRPM(Limit(lpercent) * profile->WheelMaxRPM, Limit(rpercent) * profile->WheelMaxRPM);
}

std::shared_ptr<Ultrasonic> Drivetrain::GetURCenter() {
    //This is only here in case we put back the old ultrasonic and should never be called.
    std::cout << "Crashing robot code... Drivetrain.cpp: " << __LINE__ << std::endl;
    return nullptr; //mfw segfault
}

std::shared_ptr<lib612::AnalogUltrasonic> Drivetrain::GetURSide() {
    return ur2;
}
void Drivetrain::InitDefaultCommand() {
    printf("Default command for Drivetrain\n");
    SetDefaultCommand(new Drive());
}

void Drivetrain::TankDrive(double raw_left, double raw_right){
    double l = DeadbandHandler(raw_left);
    double r = DeadbandHandler(raw_right);
    //std::cout << "Drivetrain.cpp l: " << l << " r: " << r << std::endl;
    if (l == 0) {
        drive_ml->SetVoltageRampRate(0);
        drive_ml->Set(0);
        drive_ml->SetVoltageRampRate(RAMP_RATE);
        drive_fl->Set(drive_ml->GetDeviceID());
        drive_rl->Set(drive_ml->GetDeviceID());
    } else {
        drive_ml->Set(Limit(l));
    }
    if(r == 0) {
        drive_mr->SetVoltageRampRate(0);
        drive_mr->Set(0);
        drive_mr->SetVoltageRampRate(RAMP_RATE);
        drive_fr->Set(drive_mr->GetDeviceID());
        drive_rr->Set(drive_mr->GetDeviceID());
    } else {
        drive_mr->Set(Limit(r));
    }
}

void Drivetrain::HaloDrive(double wheel, double throttle, bool isQuickTurn) {
    double over_power, angular_power;
    if (isQuickTurn) {
        if (std::abs(throttle) < 0.2) {
            m_quick_stop_accum = (1 - ALPHA) * m_quick_stop_accum + ALPHA * Limit(wheel) * 2;
        }
        over_power = 1.0;
        angular_power = wheel;
    } else {
        over_power = 0.0;
        angular_power = std::abs(throttle) * wheel * TURN_SENSITIVITY - m_quick_stop_accum;
        if (m_quick_stop_accum > 1) {
            m_quick_stop_accum -= 1;
        } else if (m_quick_stop_accum < -1) {
            m_quick_stop_accum += 1;
        } else {
            m_quick_stop_accum = 0.0;
        }
    }

    double right = throttle - angular_power;
    double left = throttle + angular_power;

    if (left > 1.0) {
        right -= over_power * (left - 1.0);
        left = 1.0;
    } else if (right > 1.0) {
        left -= over_power * (right - 1.0);
        right = 1.0;
    } else if (left < -1.0) {
        right += over_power * (-1.0 - left);
        left = -1.0;
    } else if (right < -1.0) {
        left += over_power * (-1.0 - right);
        right = -1.0;
    }
    //std::cout << "Drivetrain.cpp: Left: " << left << " Right: " << right << std::endl;
    TankDrive(left, right);
}

Drivetrain::DRIVE_MODE Drivetrain::getDriveMode() {
    return drivemode;
}

void Drivetrain::setDriveMode(Drivetrain::DRIVE_MODE mode){
    drivemode = mode;
}

double Drivetrain::DeadbandHandler(double val) {
    return (std::abs(val) > DEADBAND) ? val : 0.0;
}

double Drivetrain::Limit(double val) {
    return (std::abs(val) > 1) ? (val > 0 ? 1 : -1) : val;
}
