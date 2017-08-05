#include "Adafruit_CircuitPlayground.h"

void setup() {
  randomSeed(analogRead(0));
  CircuitPlayground.begin();
}

void loop() {
  if (CircuitPlayground.slideSwitch()) {
    //Loop through all pixels and set them to a random color
    for (int i=0; i<10; i++) {
      CircuitPlayground.setPixelColor(i, CircuitPlayground.colorWheel(random(256)));
    }
    delay(500);
  }
}
