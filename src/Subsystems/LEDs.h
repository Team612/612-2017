#pragma once

#include "WPILib.h"

enum class COLORS { RED = 0, GREEN = 1, BLUE = 2 };
enum class STATE { OFF = 0, ON = 1 };

class LEDs: public Subsystem {
    STATE state;
    COLORS color;
    std::shared_ptr<NetworkTable> led_table;
public:
    LEDs();

    void ToggleColor();
    void SetColor(COLORS c);
    void SetState(STATE s);
    COLORS GetColor();
    STATE GetState();
};
