# Author:   David Kolet-Tassara
# Date:     July 4, 2017
# Purpose:  Demonstrates the use of the neopixels on Adafruit's
#           Circuit Python. Simulates cylon scanning with USA twist.
# Required Packages:
# neopixel
# https://github.com/adafruit/Adafruit_CircuitPython_NeoPixel/releases

import board
import neopixel
import time

DELAY = .09     #Controls rate of scan, smaller is faster
RED = (60,0,0)
WHITE = (20,20,20)
BLUE = (0,0,60)


p = neopixel.NeoPixel(board.NEOPIXEL, 10)

def getColor(n):
    color = n%3
    if color == 1:
        return RED
    elif color == 2:
        return WHITE
    else:
        return BLUE

def scan(t):
    for i in range(10):
        if i+2 < 10:
            p[i] = getColor(i)
            p[i+1] = getColor(i+1)
            p[i+2] = getColor(i+2)
            p[i-1] = (0,0,0)
        elif i+1 < 10:
            p[i] = getColor(i)
            p[i+1] = getColor(i+1)
            p[i-1] = (0,0,0)
        else:
            p[i] = getColor(i)
            p[i-1] = (0,0,0)
        p.write()
        time.sleep(t)

    for i in range(8,0,-1):
        if i-2 > 0:
            p[i-2] = getColor(i-2)
            p[i-1] = getColor(i-1)
            p[i] = getColor(i)
        p[i+1] = (0,0,0)
        p.write()
        time.sleep(t)

while True:
    scan(DELAY)
