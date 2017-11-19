# Author:   David Kolet-Tassara
# Date:     June 22, 2017
# Purpose:  Demonstrates the use of the speaker on Adafruit's
#           Circuit Python. Plays a wav file.
# Required Packages:
# No additional packages Required
# IMPORTANT: The watone.wav file must be loaded on the CPX.

import audioio
import digitalio
import board

speaker = digitalio.DigitalInOut(board.SPEAKER_ENABLE)
speaker.switch_to_output(value=True)

soundfile = open("watone.wav", "rb")
a = audioio.AudioOut(board.SPEAKER, soundfile)

a.play()
