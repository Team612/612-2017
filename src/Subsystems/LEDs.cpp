#include "LEDs.h"

LEDs::LEDs() : Subsystem("LEDs") {
    led_table = NetworkTable::GetTable("LEDTable");
    SetColor(COLORS::GREEN);
    SetState(STATE::ON);
}

void LEDs::SetColor(COLORS c) {
    this->color = c;
    switch (color) {
        case COLORS::RED:
            led_table->PutString("Color", "RED");
            break;
        case COLORS::GREEN:
            led_table->PutString("Color", "GREEN");
            break;
        case COLORS::BLUE:
            led_table->PutString("Color", "BLUE");
            break;
    }
}

void LEDs::SetState(STATE s) {
    state = s;
    switch (state) {
        case STATE::OFF:
            led_table->PutBoolean("On", false);
            break;
        case STATE::ON:
            led_table->PutBoolean("On", true);
            break;
    }
}

void LEDs::ToggleColor() {
    switch(color) {
        case COLORS::RED:
            SetColor(COLORS::GREEN);
            break;
        case COLORS::GREEN:
            SetColor(COLORS::BLUE);
            break;
        case COLORS::BLUE:
            SetColor(COLORS::RED);
            break;
    }
}

STATE LEDs::GetState() {
    return state;
}

COLORS LEDs::GetColor() {
    return color;
}