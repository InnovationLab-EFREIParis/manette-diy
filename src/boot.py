try:
    import usb_hid
    #from lib.gamepad.device import gamepad
    import usb_cdc
    import storage
    import usb_midi
except ImportError:
    raise ImportError("USB_HID library is not available. Please update your CircuitPython version.")

# Disable USB mass storage cdc, and MIDI
# storage.disable_usb_drive()
usb_midi.disable()
usb_cdc.disable()

GAMEPAD_REPORT_DESCRIPTOR = bytes((
    0x05, 0x01, # USAGE_PAGE (Generic Desktop)
    0x09, 0x05, # USAGE (Game Pad)
    0xa1, 0x01, # COLLECTION (Application)
    0xa1, 0x00, #   COLLECTION (Physical)
    0x85, 0x04, #     REPORT_ID (3, default for gamepad)
    0x05, 0x09, #     USAGE_PAGE (Button)
    0x19, 0x01, #     USAGE_MINIMUM (Button 1)
    0x29, 0x10, #     USAGE_MAXIMUM (Button 16)
    0x15, 0x00, #     LOGICAL_MINIMUM (0)
    0x25, 0x01, #     LOGICAL_MAXIMUM (1)
    0x75, 0x01, #     REPORT_SIZE (1)
    0x95, 0x10, #     REPORT_COUNT (16)
    0x81, 0x02, #     INPUT (Data,Var,Abs)
    0xc0,       #   END_COLLECTION
    0xc0        # END_COLLECTION
))

gamepad = usb_hid.Device(
    report_descriptor=GAMEPAD_REPORT_DESCRIPTOR,
    usage_page=0x01,  # Generic Desktop Control
    usage=0x05,       # Gamepad
    report_ids=(4,),  # Report ID 3
    in_report_lengths=(2,),  # 10 buttons fit in 2 bytes
    out_report_lengths=(0,)   # No output reports
)

usb_hid.enable((gamepad,))
