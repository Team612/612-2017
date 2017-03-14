#pragma once

namespace PORTS {
  /*! \brief The namespace IO is a namespace that has the port number of the gunner and driver
  The name of the varuables are driver_joyport and gunner_joyport they are both const and uint32_t
  */
    namespace OI {
        const uint32_t driver_joyport = 0;
        const uint32_t gunner_joyport = 1;
    }
    /*! \brief The ANALOG namespace has nothing in it at this time
    */
    namespace ANALOG {

    }
    /*! \brief The RELAY namespace has nothing in it at this time
    */
    namespace RELAY {

    }
    /*! \brief The PWM namespace has the PWM port number value of the ultrasonic amd the servo in it
     the port number of the ultrasonic is in the analog_ultrasonic and the port number of the servo is in the servo varuable, they are both integers
    */
    namespace PWM {
        const int analog_ultrasonic = 0;
        const int servo = 1;
    }
    /*! \brief The DIO namespace has the port number of ultrasonic in and out
    they are all conts and uint32_t
    the values are in the varuables ultrasonic_in and ultrasonic_out
    ultrasonic_in is the trigger and ultrasonic_out is the echo
    */
    namespace DIO {
        const uint32_t ultrasonic_in = 0; //trigger
        const uint32_t ultrasonic_out = 1; //echo
    }
    /*! \brief The I2C namespace has nothing in it at this time
    */
    namespace I2C {

    }
    /*! \brief The CAN namespace has The port number of all the talons
    The talon numbers are all uint32_t and const
    The varuable names are drive_talonFL,drive_talonML.drive_talonRL,drive_talonFR.drive_talonMR,
    drive_talonRR,shooter_talon_left,shooter_talon_right,intake_talon_left,intake_talon_right,
    climber_talon_left, and climber_talon_right
    talons 1,2,3 are left drivetrain
    talons 4,5,6 are right drivetrain
    talon 7 is shooter left, talon 8 is shooter right
    talon 9 is intake left, talon 10 is intake right
    talon 11 is left climber, talon 12 is right climber
    */
    namespace CAN { //TODO update once the board actually is ready


        const int module = 0;
        //Drivetrain
        const uint32_t drive_talonFL = 1;
        const uint32_t drive_talonML = 3;
        const uint32_t drive_talonRL = 2;
        const uint32_t drive_talonFR = 4;
        const uint32_t drive_talonMR = 6;
        const uint32_t drive_talonRR = 5;
        //Shooter
        const uint32_t shooter_talon_left = 7;
        const uint32_t shooter_talon_right = 8;
        const uint32_t agitator = 13; //filler
        //Intake
        const uint32_t intake_talon_left = 9;
        const uint32_t intake_talon_right = 10;
        //Climber
        const uint32_t climber_talon_left = 11;
        const uint32_t climber_talon_right = 12;

        /*
            talons 1,2,3 are left drivetrain
            talons 4,5,6 are right drivetrain
            talon 7 is shooter left, talon 8 is shooter right
            talon 9 is intake left, talon 10 is intake right
            talon 11 is left climber, talon 12 is right climber
        */
    }
    /*! \brief The MXP namespace has nothing in it at this time
    */
    namespace MXP {

    }
    /*! \brief The PCM has the port number of the shifetr and compressor
    Thy are in the values shifter_forward, shifter_reverse, and compressor
    */
    namespace PCM {
        const uint32_t shifter_forward = 0;
        const uint32_t shifter_reverse = 1;
        const uint32_t compressor = 3;
    }
}
