#pragma once

#include "WPILib.h"
#include "../lib/lib612/SmoothController.h"

class OI {
private:
    std::shared_ptr<lib612::SmoothController> gunner;
    std::shared_ptr<lib612::SmoothController> driver;

public:
    OI();


    static std::unique_ptr<JoystickButton> grab_button;  /*!  The grab_button pointer is a static JoystickButton pointer it points to the button that runs the two climer talons // left bumper  */


    static std::unique_ptr<JoystickButton> align_button;  /*!  The align_button pointer is a static JoystickButton pointer it points to the button that should use vison to align to targets // right bumper  */

    static std::unique_ptr<JoystickButton> intake_button;// TODO this is not made in the constructer why is this here  /*!  The intake_button pointer is a static JoystickButton pointer it points to the button that runs the two intake talons farward  */



    static std::unique_ptr<JoystickButton> intake_clear_button; // TODO this is not made in the constructer why is this here /*!  The intake_clear_button pointer is a static JoystickButton pointer it points to the button that runs the two intake talons backward  */


    static std::unique_ptr<JoystickButton> shift_up;/*!  The shift_up pointer is a static JoystickButton pointer it points to the button that make the shifter shift to the up positon //A button  */



    static std::unique_ptr<JoystickButton> shift_down; /*!  The shift_down pointer is a static static JoystickButton pointer it points to the button that makes the shifter shift to the  down // B button  */


    static std::unique_ptr<JoystickButton> led_color; /*! The led_color pointer is a static static JoystickButton pointer it points to the button that changes the color of the led on the robot // Y button  */


    static std::unique_ptr<JoystickButton> led_power;  /*!  The led_color pointer is a static static JoystickButton pointer it points to the button that tells the led to turn off or on //X button  */
    /*! \brief returns the driver pointer
        takes no arguments
    */
    std::shared_ptr<lib612::SmoothController> getdriver();
    /*! \brief returns the gunner pointer
        takes no arguments
    */
    std::shared_ptr<lib612::SmoothController> getgunner();
};
