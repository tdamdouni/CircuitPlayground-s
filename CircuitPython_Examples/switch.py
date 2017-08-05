# Author:   David Kolet-Tassara
# Date:     June 23, 2017
# Purpose:  Demonstrates the use of the switch on Adafruit's
#           Circuit Python. Changes colors based on position.
# Required Packages:
# neopixel
# https://github.com/adafruit/Adafruit_CircuitPython_NeoPixel/releases

import digitalio
import neopixel
import board
import time

p = neopixel.NeoPixel(board.NEOPIXEL, 10)

s = digitalio.DigitalInOut(board.SLIDE_SWITCH)
s.switch_to_input(pull=digitalio.Pull.UP)

while True:
    if s.value:
        p.fill((0,25,50))
    else:
        p.fill((50,0,15))

    p.write()
    time.sleep(.01)
