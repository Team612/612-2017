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

    std::shared_ptr<lib612::SmoothController> getdriver();
    std::shared_ptr<lib612::SmoothController> getgunner();
};
