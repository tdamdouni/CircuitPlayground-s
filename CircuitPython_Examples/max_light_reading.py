# Author:   David Kolet-Tassara
# Date:     June 21, 2017
# Purpose:  Demonstrates the use of the photoresistor on Adafruit's
#           Circuit Python. Prints max light reading.
# Required Packages:
# No additional packages Required

import board
import time
import analogio

light = analogio.AnalogIn(board.LIGHT)
x = 0

while True:
    r = light.value
    if x < r:
        x = r
        print(x)

    time.sleep(.1)
