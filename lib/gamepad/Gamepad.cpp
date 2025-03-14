#include <PlatformMutex.h>
#include "usb_phy_api.h"
#include "PluggableUSBHID.h"
#include "Gamepad.h"

static const uint8_t gamepad_desc_hid_report[] = {
    0x05, 0x01, // USAGE_PAGE (Generic Desktop)
    0x09, 0x05, // USAGE (Game Pad)
    0xa1, 0x01, // COLLECTION (Application)
    0xa1, 0x00, //   COLLECTION (Physical)
    // 0x85, 0x03, //     REPORT_ID (3, default for gamepad)
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

Gamepad::Gamepad(bool connect_blocking, uint16_t vendor_id, uint16_t product_id, uint16_t product_release) : USBHID(get_usb_phy(), 0, 0, vendor_id, product_id, product_release)
{
    reportLength = sizeof(gamepad_desc_hid_report);
}

void Gamepad::sendReport()
{
    _mutex.lock();
    HID_REPORT hid_report;
    hid_report.data[0] = LSB(report);
    hid_report.data[1] = MSB(report);
    hid_report.length = 2;
    send(&hid_report);
    _mutex.unlock();
}

void Gamepad::setButton(report_bit_t button, bool state)
{
    _mutex.lock();
    if (state == 1)
    {
        bitSet(report, button);
    }
    else
    {
        bitClear(report, button);
    }
    _mutex.unlock();
}

const uint8_t *Gamepad::report_desc()
{
    reportLength = sizeof(gamepad_desc_hid_report);
    return gamepad_desc_hid_report;
}

uint16_t Gamepad::report_desc_length()
{
    return sizeof(gamepad_desc_hid_report);
}

// const uint8_t *Gamepad::configuration_desc(uint8_t index)
// {
//     if (index != 0)
//     {
//         return NULL;
//     }

//     uint8_t configuration_descriptor_temp[] = {
//         0x09, // bLength
//         0x02, // bDescriptorType
//         0x22, // wTotalLength (LSB)
//         0x00, // wTotalLength (MSB)
//         0x01, // bNumInterfaces
//         0x01, // bConfigurationValue
//         0x00, // iConfiguration
//         C_RESERVED | C_SELF_POWERED, // bmAttributes
//         C_SELF_POWERED, // bMaxPower

//         // Interface Descriptor
//         0x09, // bLength
//         0x04, // bDescriptorType
//         pluggedInterface, // bInterfaceNumber
//         0x00, // bAlternateSetting
//         0x01, // bNumEndpoints
//         0x03, // bInterfaceClass
//         0x00, // bInterfaceSubClass
//         0x00, // bInterfaceProtocol
//         0x00, // iInterface

//         // HID Descriptor
//         0x09,                                            // bLength
//         0x21,                                            // bDescriptorType ---
//         0x11,                                            // bcdHID (LSB)
//         0x01,                                            // bcdHID (MSB)
//         0x00,                                            // bCountryCode
//         0x01,                                            // bNumDescriptors
//         0x22,                                            // bDescriptorType
//         (uint8_t)(LSB(sizeof(gamepad_desc_hid_report))), // wDescriptorLength (LSB)
//         (uint8_t)(MSB(sizeof(gamepad_desc_hid_report))), // wDescriptorLength (MSB)

//         // Endpoint Descriptor (Interrupt IN)
//         0x07, // bLength
//         0x05, // bDescriptorType
//         _int_in, // bEndpointAddress
//         0x03, // bmAttributes
//         0x40, // wMaxPacketSize (LSB)
//         0x00, // wMaxPacketSize (MSB)
//         5,    // bInterval (milliseconds)
//     };

//     memcpy(_configuration_descriptor, configuration_descriptor_temp, sizeof(configuration_descriptor_temp));

//     return _configuration_descriptor;
// }
