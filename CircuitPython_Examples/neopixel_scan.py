# Author:   David Kolet-Tassara
# Date:     June 16, 2017
# Purpose:  Demonstrates the use of the neopixels on Adafruit's
#           Circuit Python. Simulates cylon scanning.
# Required Packages:
# neopixel
# https://github.com/adafruit/Adafruit_CircuitPython_NeoPixel/releases
# adafruit_thermistor

import time
import board
import neopixel

DELAY = .07
COLOR = (0, 0, 50)

PIX = neopixel.NeoPixel(board.NEOPIXEL, 10)

def scan(tme, col):
    for i in range(10):
        PIX[i] = col
        PIX[i-1] = (0, 0, 0)
        PIX.write()
        time.sleep(tme)

    for i in range(8, 0, -1):
        PIX[i] = col
        PIX[i+1] = (0, 0, 0)
        PIX.write()
        time.sleep(tme)

while True:
    scan(DELAY, COLOR)
