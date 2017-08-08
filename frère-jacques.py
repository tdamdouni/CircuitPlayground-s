import nativeio
import time
from board import SPEAKER


notes = {
  'b': 26,
  'a#': 27,
  'a': 28,
  'g#': 29,
  'g': 31,
  'f#': 33,
  'f': 35,
  'e': 37,
  'd#': 40,
  'd': 42,
  'c#': 45,
  'c': 48,
}


def bloop(oscillate_on, duration, speaker):
    for i in range(duration):
        if i % oscillate_on:
            speaker.value = 1
        else:
            speaker.value = 0
    speaker.value = 0  # ensure the speaker remains off
    time.sleep(0.01)  # add articulation


def play(tune, speaker):
    for note in tune:
        name, duration = note.split(':')
        bloop(notes[name], int(duration) * 1000, speaker)


line1 = ['c:4', 'd:4', 'e:4', 'c:4']
line2 = ['e:4', 'f:4', 'g:8']
line3 = ['g:2', 'a:2', 'g:2', 'f:2', 'e:4', 'c:4']
line4 = ['c:4', 'g:4', 'c:8']
frere_jaques = line1 * 2 + line2 * 2 + line3 * 2 + line4 * 2


with nativeio.DigitalInOut(SPEAKER) as speaker:
    speaker.switch_to_output()
    play(frere_jaques, speaker)