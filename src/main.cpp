/*
    Gamepad.cpp
    A GamePad HID library for custom gamepads

    Copyright (C) 2025 Innovation Lab - Efrei Paris
    Copyright (C) 2025 ICE Efrei

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <Arduino.h>
#include "Gamepad.h"

#define N_BUTTONS 10

#define PIN_BLUE_LED 15

#define PIN_UP 10
#define PIN_LEFT 11
#define PIN_RIGHT 12
#define PIN_DOWN 13
#define PIN_SELECT 14
#define PIN_CROSS 17
#define PIN_SQUARE 18
#define PIN_CIRCLE 19
#define PIN_TRIANGLE 20
#define PIN_START 16

static const uint8_t pins[] = {
    PIN_CROSS,
    PIN_CIRCLE,
    PIN_TRIANGLE,
    PIN_SQUARE,
    PIN_DOWN,
    PIN_RIGHT,
    PIN_UP,
    PIN_LEFT,
    PIN_START,
    PIN_SELECT
};

static const uint8_t report_ids[] = {
    REPORT_CROSS,
    REPORT_CIRCLE,
    REPORT_TRIANGLE,
    REPORT_SQUARE,
    REPORT_DOWN,
    REPORT_RIGHT,
    REPORT_UP,
    REPORT_LEFT,
    REPORT_START,
    REPORT_SELECT
};

bool previous_states[N_BUTTONS] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1};

bool any_button_changed = false;

uint16_t report = 0;

void setup()
{
    for (uint8_t i = 0; i < N_BUTTONS; i++)
    {
        pinMode(pins[i], INPUT_PULLUP);
    }

    pinMode(PIN_BLUE_LED, OUTPUT);
}

void loop()
{
    any_button_changed = false;

    for (uint8_t i = 0; i < N_BUTTONS; i++)
    {
        bool v = digitalRead(pins[i]);
        if (v != previous_states[i])
        {
            any_button_changed = true;

            previous_states[i] = v;

            Controller.setButton((report_bit_t)report_ids[i], !v);
        }
    }

    if (any_button_changed)
    {
        Controller.sendReport();
    }
}
