#pragma once

namespace PORTS {
    namespace OI {
        const uint32_t driver_joyport = 0;
        const uint32_t gunner_joyport = 1;
    }

    namespace ANALOG {

    }

    namespace RELAY {

    }

    namespace PWM {
        const int analog_ultrasonic = 0;
        const int servo = 1;
        const int climber = 2;
    }

    namespace DIO {
        const uint32_t ultrasonic_in = 0; //trigger
        const uint32_t ultrasonic_out = 1; //echo
    }

    namespace I2C {

    }

    namespace CAN { //TODO update once the board actually is ready


        const int module = 0;
        //Drivetrain
        const uint32_t drive_talonFL = 1;
        const uint32_t drive_talonML = 2; // 3
        const uint32_t drive_talonRL = 60; // 2
        const uint32_t drive_talonFR = 4;
        const uint32_t drive_talonMR = 6;
        const uint32_t drive_talonRR = 11; // 5
        //Shooter
        const uint32_t shooter_talon_left = 7;

        const uint32_t shooter_talon_right = 8;
        const uint32_t agitator = 73; // filler
        //Intake
        const uint32_t intake_talon_left = 9;
        const uint32_t intake_talon_right = 10;
        //Climber
        const uint32_t climber_talon_left = 71; // 11 filler
        const uint32_t climber_talon_right = 72; // filler

        /*
            talons 1,2,3 are left drivetrain
            talons 4,5,6 are right drivetrain
            talon 7 is shooter left, talon 8 is shooter right
            talon 9 is intake left, talon 10 is intake right
            talon 11 is left climber, talon 12 is right climber
        */
    }

    namespace MXP {

    }

    namespace PCM {
        const uint32_t shifter_forward = 0;
        const uint32_t shifter_reverse = 1;
        const uint32_t compressor = 3;
        const uint32_t gear_forward = 4;
        const uint32_t gear_reverse = 5;
    }
}
