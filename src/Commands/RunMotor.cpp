#include "RunMotor.h"
#include "../Robot.h"


RunMotor::RunMotor(float power) {

    this->power = power;
    SetTimeout(1.0f);

}



void RunMotor::Initialize() {

    RobotMap::talon_shoot->Set(power);

}



void RunMotor::Execute() {



}



bool RunMotor::IsFinished() {

    return IsTimedOut();

}



void RunMotor::End() {

    RobotMap::talon_shoot->Set(0.0f);

}



void RunMotor::Interrupted() {

  RobotMap::talon_shoot->Set(0.0f);

}
