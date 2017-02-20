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

    std::shared_ptr<XboxController> getdriver();
    std::shared_ptr<XboxController> getgunner();
};
