from adafruit_hid import find_device
from usb_hid import devices, Device
try:
    from typing import Iterable
except ImportError:
    pass


class Gamepad:
    cross = 0
    circle = 1
    square = 2
    triangle = 3
    select = 8
    start = 9
    up = 12
    left = 13
    down = 14
    right = 15

    def __init__(self):
        self.report = bytearray((0x00, 0x00))
        self.device:Device = find_device(devices, usage_page=0x01, usage=0x05, timeout=1)
        # self.device = devices[0]
    
    def press(self, button: int | Iterable[int]) -> None:
        if (isinstance(button, int)):
            button = [button]
        
        for b in button:
            if (b < 0 or b > 15): 
                continue
            if (b < 8): 
                self.report[0] |= (0x01 << b)
                continue
            if (b < 16):
                self.report[1] |= (0x01 << (b - 8))
                continue

    def release(self, button) -> None:
        if (isinstance(button, int)):
            button = [button]
        
        for b in button:
            if (b < 0 or b > 15): 
                continue
            if (b < 8): 
                self.report[0] &= ~(0x01 << b)
                continue
            if (b < 16):
                self.report[1] &= ~(0x01 << (b - 8))

    def send(self) -> None:
        self.device.send_report(self.report)

    def release_all(self) -> None:
        self.report[0] = 0x00
        self.report[1] = 0x00

gamepad = Gamepad()
