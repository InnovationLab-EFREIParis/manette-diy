/*
    Gamepad.h
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

#ifndef GAMEPAD_H
#define GAMEPAD_H

#include <Arduino.h>
#include <HID.h>

#ifdef _USING_HID


class Gamepad
{
    private:
    uint16_t buttonsStates;

public:
    Gamepad();

    void sendUpdate();

    void set(uint8_t button, bool state);
};

#else
#warning "HID is not supported for this chip"
#endif
#endif