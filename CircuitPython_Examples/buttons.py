# Author:   David Kolet-Tassara
# Date:     June 23, 2017
# Purpose:  Demonstrates the use of the accelerometer on Adafruit's
#           Circuit Python. Shows green when "level".
# Required Packages:
# neopixel
# https://github.com/adafruit/Adafruit_CircuitPython_NeoPixel/releases

import board
import digitalio
import neopixel

p = neopixel.NeoPixel(board.NEOPIXEL, 10)

#Initialize Buttons A and B
button_a = digitalio.DigitalInOut(board.BUTTON_A)
button_a.switch_to_input(pull=digitalio.Pull.DOWN)

button_b = digitalio.DigitalInOut(board.BUTTON_B)
button_b.switch_to_input(pull=digitalio.Pull.DOWN)


def blue_star():
    for i in range(10):
        if i%2 == 0:
            p[i] = (0,15,50)
        else:
            p[i] = (0,0,0)
    p.write()

def white_circle():
    for i in range(10):
        p[i] = (25, 25, 25)
    p.write()

def black():
    for i in range(10):
        p[i] = (0, 0, 0)
    p.write()


while True:

    if button_a.value:
        blue_star()
    elif button_b.value:
        white_circle()
    else:
        black()
