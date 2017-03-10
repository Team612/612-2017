#include "ChangeLED.h"

#include "../../Robot.h"

ChangeLED::ChangeLED() : Command("LED On Off") {
    std::cout << "ChangeLED.cpp: " << __LINE__ << " constructor called" << std::endl;
    Requires(Robot::leds.get());
    std::cout << "ChangeLED.cpp: " << __LINE__ << std::endl;
}

void ChangeLED::Initialize() {
    Robot::leds->ToggleColor();
}

void ChangeLED::Execute() { }

bool ChangeLED::IsFinished() {
    return true;
}

void ChangeLED::End() { }

void ChangeLED::Interrupted() { }