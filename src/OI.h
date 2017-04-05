#pragma once

#include "WPILib.h"
#include "lib612/SmoothController.h"

class OI {
private:
    std::shared_ptr<lib612::SmoothController> gunner;
    std::shared_ptr<lib612::SmoothController> driver;

public:
    OI();

    static std::unique_ptr<JoystickButton> grab_button;
    static std::unique_ptr<JoystickButton> align_left;
    static std::unique_ptr<JoystickButton> align_right;
    static std::unique_ptr<JoystickButton> intake_button;
    static std::unique_ptr<JoystickButton> intake_clear_button;
    static std::unique_ptr<JoystickButton> shift_up;
    static std::unique_ptr<JoystickButton> shift_down;
    static std::unique_ptr<JoystickButton> led_color;
    static std::unique_ptr<JoystickButton> led_power;
    static std::unique_ptr<JoystickButton> gear_open_button;
    static std::unique_ptr<JoystickButton> gear_close_button;

    std::shared_ptr<lib612::SmoothController> getdriver();
    std::shared_ptr<lib612::SmoothController> getgunner();
};
