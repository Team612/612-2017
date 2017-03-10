#include "LEDOnOff.h"

#include "../../Subsystems/LEDs.h"
#include "../../Robot.h"

LEDOnOff::LEDOnOff() : Command("LED On Off") {
    //std::cout << "LEDOnOff.cpp: " << __LINE__ << " constructor called" << std::endl;
    Requires(Robot::leds.get());
    //std::cout << "LEDOnOff.cpp: " << __LINE__ << std::endl;
}

void LEDOnOff::Initialize() {
    if(Robot::leds->GetState() == STATE::OFF)
        Robot::leds->SetState(STATE::ON);
    else
        Robot::leds->SetState(STATE::OFF);
}

void LEDOnOff::Execute() { }

bool LEDOnOff::IsFinished() {
    return true;
}

void LEDOnOff::End() { }

void LEDOnOff::Interrupted() { }
