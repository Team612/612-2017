#include "OI.h"
#include "Ports.h"

#include "Commands/Vision/HorizontalAlign.h"
#include "Commands/Climber/Climb.h"
#include "Commands/Drive/Drive.h"
#include "Commands/Drive/DriveDistance.h"
#include "Commands/Drive/Shift.h"
#include "Commands/Shooter/Shoot.h"
#include "Commands/Climber/Grab.h"
#include "Commands/Internal/IntakeFuel.h"
#include "Commands/Vision/AutoAlign.h"
#include "Commands/Internal/ChangeLED.h"
#include "Commands/Internal/LEDOnOff.h"

std::unique_ptr<JoystickButton> OI::grab_button;
std::unique_ptr<JoystickButton> OI::align_left;
std::unique_ptr<JoystickButton> OI::align_right;
std::unique_ptr<JoystickButton> OI::intake_button;
std::unique_ptr<JoystickButton> OI::intake_clear_button;
std::unique_ptr<JoystickButton> OI::shift_up;
std::unique_ptr<JoystickButton> OI::shift_down;
std::unique_ptr<JoystickButton> OI::led_color;
std::unique_ptr<JoystickButton> OI::led_power;

OI::OI() {
    gunner.reset(new lib612::SmoothController(PORTS::OI::gunner_joyport));
    //grab_button = std::make_unique<JoystickButton>(gunner.get(), 5); //left bumper
    //grab_button->WhenPressed(new Grab()); //Not on robot
    align_left = std::make_unique<JoystickButton>(gunner.get(), 2); //B button
    align_left->WhenPressed(new AutoAlign(HorizontalFind::RIGHT));
    align_right = std::make_unique<JoystickButton>(gunner.get(), 3);
    align_right->WhenPressed(new AutoAlign(HorizontalFind::LEFT));

    driver.reset(new lib612::SmoothController(PORTS::OI::driver_joyport));
    shift_up = std::make_unique<JoystickButton>(driver.get(), 1); //A button
    shift_up->WhenPressed(new Shift(Shift::SHIFT_DIR::UP));
    shift_down = std::make_unique<JoystickButton>(driver.get(), 2); //B button
    shift_down->WhenPressed(new Shift(Shift::SHIFT_DIR::DOWN));
    led_power = std::make_unique<JoystickButton>(driver.get(), 3); //X button
    led_power->WhenPressed(new LEDOnOff());
    led_color = std::make_unique<JoystickButton>(driver.get(), 4); //Y button
    led_color->WhenPressed(new ChangeLED());

    // SmartDashboard Buttons
    //These just clutter up EvenSmarterDashboard
    /*SmartDashboard::PutData("MoveBalls", new IntakeFuel(true));
    SmartDashboard::PutData("Move", new Climb());
    //SmartDashboard::PutData("DriveDistance", new DriveDistance());
    SmartDashboard::PutData("Gear", new Gear());
    SmartDashboard::PutData("AlignToTarget", new AlignToTarget());
    SmartDashboard::PutData("Shoot", new Shoot());
    SmartDashboard::PutData("Drive", new Drive());
    SmartDashboard::PutData("DriveDistance", new DriveDistance(SmartDashboard::GetNumber("Distance (m)", 0.5)));*/
}

std::shared_ptr<lib612::SmoothController> OI::getdriver() {
   return driver;
}

std::shared_ptr<lib612::SmoothController> OI::getgunner() {
   return gunner;
}
