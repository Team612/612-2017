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
        const int servo = 0;
    }

    namespace DIO {
        const uint32_t ultrasonic_in = 0;
        const uint32_t ultrasonic_out = 1;
    }

    namespace I2C {

    }

    namespace CAN { //TODO update once the board actually is ready

        const int module = 0;
        //Drivetrain
        const uint32_t drive_talonFL = 1;
        const uint32_t drive_talonML = 2;
        const uint32_t drive_talonRL = 3;
        const uint32_t drive_talonFR = 4;
        const uint32_t drive_talonMR = 5;
        const uint32_t drive_talonRR = 6;
        //Shooter
        const uint32_t shooter_talon_left = 7;
        const uint32_t shooter_talon_right = 8;
        //Intake
        const uint32_t intake_talon_left = 9;
        const uint32_t intake_talon_right = 10;
        //Climber
        const uint32_t climber_talon_left = 11;
        const uint32_t climber_talon_right = 12;


        /*const uint32_t shooter = 6;
        const uint32_t drive_talonFR = 1;
        const uint32_t drive_talonFL = 2;
        const uint32_t drive_talonMR = 3;
        const uint32_t drive_talonML = 7;
        const uint32_t drive_talonRR = 4;
        const uint32_t drive_talonRL = 5;
        const uint32_t intake_talon_left = 8; //This is 7 on the soda branch, not possible for both to be right
        const uint32_t intake_talon_right = 9;
        const uint32_t climber = 10;
        const int module = 0;*/

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
        
    }
}
