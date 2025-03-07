#include <Arduino.h>

// Including a library
#include "Gamepad.h"

#define PIN_PADDING 2

// Initializing a Gamepad
Gamepad gp(true);

bool prev[4] = {1};

void setup()
{
    for (uint8_t i = 0; i < 4; i++)
    {
        pinMode(i + PIN_PADDING, INPUT_PULLUP);
    }
    // Serial.begin(9600);
    // while (!Serial);
    // Serial.println("begin");
}

void loop()
{
    for (uint8_t i = 0; i < 4; i++)
    {
        bool v = digitalRead(i + PIN_PADDING);
        if (v != prev[i])
        {
            prev[i] = v;
            gp.setButtonState(i, !v);
            // Serial.print("input : ");
            // Serial.println(i);
        }
    }
}