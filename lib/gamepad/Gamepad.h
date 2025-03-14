#ifndef GAMEPAD_H
#define GAMEPAD_H

#include <PluggableUSBHID.h>
#include <PlatformMutex.h>

#define TOTAL_DESCRIPTOR_LENGTH ((1 * CONFIGURATION_DESCRIPTOR_LENGTH) \
                               + (1 * INTERFACE_DESCRIPTOR_LENGTH) \
                               + (1 * HID_DESCRIPTOR_LENGTH) \
                               + (2 * ENDPOINT_DESCRIPTOR_LENGTH))

using namespace arduino; 

enum report_bit_t
{
    REPORT_CROSS = 0,
    REPORT_SQUARE = 1,
    REPORT_CIRCLE = 2,
    REPORT_TRIANGLE = 3,
    REPORT_SELECT = 8,
    REPORT_DOWN = 13,
    REPORT_START = 9,
    REPORT_UP = 12,
    REPORT_LEFT = 14,
    REPORT_RIGHT = 15
};

class Gamepad: public USBHID {
public:
    Gamepad(bool connect_blocking = true, uint16_t vendor_id = 0x1234, uint16_t product_id = 0x0001, uint16_t product_release = 0x0001);
    void sendReport();
    void setButton(report_bit_t button, bool state);
    const uint8_t *report_desc();
    uint16_t report_desc_length();

protected:
    // virtual const uint8_t *configuration_desc(uint8_t index);

private:
    uint16_t report;
    PlatformMutex _mutex;
    uint8_t _configuration_descriptor[34];
};

static Gamepad Controller;

#endif