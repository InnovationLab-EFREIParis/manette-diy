import board
from digitalio import DigitalInOut, Direction, Pull
import time
import usb_hid
from lib.gamepad import gamepad


class Button:
    def __init__(self, pin, button_id):
        self.pin = DigitalInOut(pin)
        self.pin.direction = Direction.INPUT
        self.pin.pull = Pull.UP
        self.report_id = button_id
        self.previous_state = 1
    
    def update(self):
        v = self.pin.value
        if v != self.previous_state:
            self.previous_state = v
            if (v == 0):
                gamepad.press(self.report_id)
                return True
            else:
                gamepad.release(self.report_id)
                return True
        return False

buttons = [
    Button(board.GP17, gamepad.cross),
    Button(board.GP18, gamepad.square),
    Button(board.GP19, gamepad.circle),
    Button(board.GP20, gamepad.triangle),
    Button(board.GP16, gamepad.start),
    Button(board.GP14, gamepad.select),
    Button(board.GP13, gamepad.down),
    Button(board.GP12, gamepad.right),
    Button(board.GP11, gamepad.left),
    Button(board.GP10, gamepad.up),
]

while True:
    anything_changed = False

    for b in buttons:
        if b.update():
            anything_changed = True
    
    if anything_changed:
        gamepad.send()
