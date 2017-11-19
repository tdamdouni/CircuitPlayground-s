#include "Adafruit_CircuitPlayground.h"

static int notes[]    = { 523,  523,  523,  587,  659,
                          659,  587,  659,  698,  784,
                         1046, 1046, 1046,  784,  784,  784,
                          659,  659,  659,  523,  523,  523,
                          784,  698,  659,  587,  523};

static int duration[] = {   3,    3,    2,    1,    3,
                            2,    1,    2,    1,    6,
                            1,    1,    1,    1,    1,    1,
                            1,    1,    1,    1,    1,    1,
                            2,    1,    2,    1,    6};

void playNote(int frequency, int duration);

void setup() {
  CircuitPlayground.begin();
}

void loop() {
  if (CircuitPlayground.leftButton()) {
    for (int i=0; i<27; i++) {
      playNote(notes[i], duration[i]);
    }
  }
}

void playNote(int frequency, int duration) {
  CircuitPlayground.playTone(frequency, duration * 150);
  delay(duration * 160);
}

