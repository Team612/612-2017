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
    }

    namespace I2C {

    }

    namespace CAN {
        const uint32_t shoot_talon00 = 6;
        const uint32_t drive_talonFR = 7;
        const uint32_t drive_talonFL = 1;
        const uint32_t drive_talonRR = 3;
        const uint32_t drive_talonRL = 5;
        const uint32_t conveyor_talon = 8;
        const uint32_t climber_talon = 6;


    }

    namespace MXP{

    }
}
