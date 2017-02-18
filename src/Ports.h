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
    }

    namespace I2C {

    }

    namespace CAN { //TODO update once the board actually is ready
        const uint32_t shoot_l = 6;
        const uint32_t shoot_r = 6;
        const uint32_t drive_talonFR = 7;
        const uint32_t drive_talonFL = 1;
        const uint32_t drive_talonMR = 1;
        const uint32_t drive_talonML = 2;
        const uint32_t drive_talonRR = 3;
        const uint32_t drive_talonRL = 5;
        const uint32_t intake_talon_left = 10; //This is 7 on the soda branch, not possible for both to be right
        const uint32_t intake_talon_right = 8;
        const uint32_t climber_l = 6;


    }

    namespace MXP{

    }
}
