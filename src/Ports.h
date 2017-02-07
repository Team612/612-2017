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

    }

    namespace DIO {
        const uint32_t drivetrainleft_encoder00 = 0;
        const uint32_t drivetrainleft_encoder01 = 1;
        const uint32_t drivetrainright_encoder00 = 2;
        const uint32_t drivetrainright_encoder01 = 3;
        const uint32_t shooter_encoder = 4;
    }

    namespace I2C {

    }

    namespace CAN { //TODO update once the board actually is ready
        const uint32_t left_shoot_talon = 6;
        const uint32_t right_shoot_talon = 4;
        const uint32_t drive_talonFR = 7;
        const uint32_t drive_talonFL = 1;
        const uint32_t drive_talonRR = 3;
        const uint32_t drive_talonRL = 5;
        const uint32_t intake_talon_left = 10; //This is 7 on the soda branch, not possible for both to be right
        const uint32_t intake_talon_right = 8;
        const uint32_t climber_talon_left = 6;
        const uint32_t climber_talon_right = 2;


    }

    namespace MXP{

    }
}
