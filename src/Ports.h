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
    }

    namespace I2C {

    }

    namespace CAN { //TODO update once the board actually is ready
        const uint32_t shoot_l = 6;
	const uint32_t shoot_r = 6;
        const uint32_t drive_talonFR = 1;
        const uint32_t drive_talonFL = 2;
        const uint32_t drive_talonMR = 3;
        const uint32_t drive_talonML = 7;
        const uint32_t drive_talonRR = 4;
        const uint32_t drive_talonRL = 5;
        const uint32_t intake_talon_left = 8; //This is 7 on the soda branch, not possible for both to be right
        const uint32_t intake_talon_right = 9;
        const uint32_t climber_l = 10;
    }

    namespace MXP {

    }

    namespace PDP {
        const int module = 0; //TODO What is this?
    }
}
