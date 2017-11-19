# Author:   David Kolet-Tassara
# Date:     June 19, 2017
# Purpose:  Demonstrates the use of the accelerometer on Adafruit's
#           Circuit Python. Shows green when "level".
# Required Packages:
# neopixel
# https://github.com/adafruit/Adafruit_CircuitPython_NeoPixel/releases
# adafruit_lis3dh
# https://github.com/adafruit/Adafruit_CircuitPython_LIS3DH

import board
import neopixel
import time
import busio
import adafruit_lis3dh

ACCEL_RANGE   = adafruit_lis3dh.RANGE_16_G

p = neopixel.NeoPixel(board.NEOPIXEL, 10)

i2c = busio.I2C(board.ACCELEROMETER_SCL, board.ACCELEROMETER_SDA)
lis3dh = adafruit_lis3dh.LIS3DH_I2C(i2c, address=25)

lis3dh.range = ACCEL_RANGE

while True:

    if(lis3dh.acceleration[0] < 1 and lis3dh.acceleration[0] > -1):
        p.fill((0,50,10))
    elif(lis3dh.acceleration[0] < 3 and lis3dh.acceleration[0] > -3):
        p.fill((0,0,50))
    elif(lis3dh.acceleration[0] < 6 and lis3dh.acceleration[0] > -6):
        p.fill((25, 0, 25))
    elif(lis3dh.acceleration[0] < 10 and lis3dh.acceleration[0] > -10):
        p.fill((50, 0, 10))
    else:
        p.fill((0,0,0))

    p.write()
    time.sleep(.05)
