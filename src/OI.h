#pragma once

#include "WPILib.h"

class OI {
private:
    std::shared_ptr<frc::XboxController> gunner;
    std::shared_ptr<frc::XboxController> driver;

public:
    OI();

    static std::unique_ptr<JoystickButton> grab_button;
    static std::unique_ptr<JoystickButton> align_button;
    static std::unique_ptr<JoystickButton> intake_button;
    static std::unique_ptr<JoystickButton> intake_clear_button;
    static std::unique_ptr<JoystickButton> shift_up;
    static std::unique_ptr<JoystickButton> shift_down;

    std::shared_ptr<XboxController> getdriver();
    std::shared_ptr<XboxController> getgunner();
};
