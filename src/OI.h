#pragma once

#include "WPILib.h"
#include "../lib/lib612/SmoothController.h"

class OI {
private:
    std::shared_ptr<lib612::SmoothController> gunner;
    std::shared_ptr<lib612::SmoothController> driver;

public:
    OI();

    static std::unique_ptr<JoystickButton> grab_button;
    static std::unique_ptr<JoystickButton> align_button;
    static std::unique_ptr<JoystickButton> intake_button;
    static std::unique_ptr<JoystickButton> intake_clear_button;
    static std::unique_ptr<JoystickButton> shift_up;
    static std::unique_ptr<JoystickButton> shift_down;

    std::shared_ptr<lib612::SmoothController> getdriver();
    std::shared_ptr<lib612::SmoothController> getgunner();
};
