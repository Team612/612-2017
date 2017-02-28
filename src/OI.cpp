#include "OI.h"
#include "Ports.h"

#include "Commands/Vision/HorizontalAlign.h"
#include "Commands/Climber/Climb.h"
#include "Commands/Drive/Drive.h"
#include "Commands/Drive/DriveDistance.h"
#include "Commands/Drive/Shift.h"
#include "Commands/Gear/Gear.h"
#include "Commands/Shooter/Shoot.h"
#include "Commands/Climber/Grab.h"
#include "Commands/Internal/IntakeFuel.h"

std::unique_ptr<JoystickButton> OI::grab_button;
std::unique_ptr<JoystickButton> OI::align_button;
std::unique_ptr<JoystickButton> OI::intake_button;
std::unique_ptr<JoystickButton> OI::intake_clear_button;
std::unique_ptr<JoystickButton> OI::shift_up;
std::unique_ptr<JoystickButton> OI::shift_down;

OI::OI() {
    gunner.reset(new lib612::SmoothController(PORTS::OI::gunner_joyport));
    grab_button = std::make_unique<JoystickButton>(gunner.get(), 5); //left bumper
    grab_button->WhenPressed(new Grab());
    align_button = std::make_unique<JoystickButton>(gunner.get(), 6); //right bumper
    //intake_button = std::make_unique<JoystickButton>(gunner.get(), 2); //B button
    //intake_button->WhileHeld(new IntakeFuel(true));
    //intake_clear_button = std::make_unique<JoystickButton>(gunner.get(), 2); //A button
    //intake_clear_button->WhileHeld(new IntakeFuel(false));


    driver.reset(new lib612::SmoothController(PORTS::OI::driver_joyport));
    shift_up = std::make_unique<JoystickButton>(driver.get(), 5);
    shift_up->WhenPressed(new Shift(Shift::SHIFT_DIR::UP));
    shift_down = std::make_unique<JoystickButton>(driver.get(), 6);
    shift_down->WhenPressed(new Shift(Shift::SHIFT_DIR::DOWN));
    align_button->WhenPressed(new HorizontalAlign(0, true));
    intake_button = std::make_unique<JoystickButton>(gunner.get(), 2); //B button
    intake_button->WhileHeld(new IntakeFuel(true));
    intake_clear_button = std::make_unique<JoystickButton>(gunner.get(), 2); //A button
    intake_clear_button->WhileHeld(new IntakeFuel(false));

    // SmartDashboard Buttons
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
