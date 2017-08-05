# Author:   David Kolet-Tassara
# Date:     July 11, 2017
# Purpose:  Uses the CP accelerometer to calculate general magnitude of
#           acceleration forces
# Required Packages:
# adafruit_lis3dh
# https://github.com/adafruit/Adafruit_CircuitPython_LIS3DH

import board
import time
import busio
import math
import adafruit_lis3dh

ACCEL_RANGE   = adafruit_lis3dh.RANGE_16_G

i2c = busio.I2C(board.ACCELEROMETER_SCL, board.ACCELEROMETER_SDA)
lis3dh = adafruit_lis3dh.LIS3DH_I2C(i2c, address=25)
lis3dh.range = ACCEL_RANGE

while True:

    #magnitude is just the squareroot of the sum of x, y, & z's squares
    x = lis3dh.acceleration[0]**2
    y = lis3dh.acceleration[1]**2
    z = lis3dh.acceleration[2]**2
    mag = math.sqrt(x+y+z)

    print(mag)
