/*
    Gamepad.cpp
    A GamePad HID library for custom gamepads

    Copyright (C) 2016 Marek GAMELASTER Kraus
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

#if defined(_USING_HID)

Gamepad::Gamepad()
{

    static const uint8_t ReportDescriptor[] PROGMEM = {
        0x05, 0x01, // USAGE_PAGE (Generic Desktop)
        0x09, 0x05, // USAGE (Game Pad)
        0xa1, 0x01, // COLLECTION (Application)
        0xa1, 0x00, //   COLLECTION (Physical)
        0x85, 0x03, //     REPORT_ID (3, default for gamepad)
        0x05, 0x09, //     USAGE_PAGE (Button)
        0x19, 0x01, //     USAGE_MINIMUM (Button 1)
        0x29, 0x10, //     USAGE_MAXIMUM (Button 16)
        0x15, 0x00, //     LOGICAL_MINIMUM (0)
        0x25, 0x01, //     LOGICAL_MAXIMUM (1)
        0x75, 0x01, //     REPORT_SIZE (1)
        0x95, 0x10, //     REPORT_COUNT (16)
        0x81, 0x02, //     INPUT (Data,Var,Abs)
        0xc0,       //   END_COLLECTION
        0xc0        // END_COLLECTION
    };
    static HIDSubDescriptor gamePadDescriptor(ReportDescriptor, sizeof(ReportDescriptor));
    HID().AppendDescriptor(&gamePadDescriptor);

    buttonsStates = 0;
}

void Gamepad::set(uint8_t button, bool state)
{
    if (state == true)
        bitSet(buttonsStates, button);
    else
        bitClear(buttonsStates, button);
    sendUpdate();
}

void Gamepad::sendUpdate()
{
    HID().SendReport(0x03, &buttonsStates, sizeof(buttonsStates));
}

#endif