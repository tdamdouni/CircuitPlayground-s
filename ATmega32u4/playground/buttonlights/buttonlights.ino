#include <Adafruit_CircuitPlayground.h>
#include "lights.h"

#define IN_ORDER 1
#define SCATTER 3

const int DELAY_MILLIS = 50;
const int INITIAL_BRIGHTNESS = 80;
const int NUMBER_OF_PULSES = 5;
const int PULSE_DELAY_MILLIS = 2;

bool right_button_pressed = false;

void setup() {
  CircuitPlayground.begin();
}

void loop() {
  if (!CircuitPlayground.rightButton()) {
    right_button_pressed = false;
    return;
  }

  if (!right_button_pressed) {
    CircuitPlayground.setBrightness(INITIAL_BRIGHTNESS);
    light_loop(DELAY_MILLIS, IN_ORDER, clockwise);
    pulse(NUMBER_OF_PULSES, PULSE_DELAY_MILLIS);
    CircuitPlayground.clearPixels();
    CircuitPlayground.setBrightness(INITIAL_BRIGHTNESS);
    light_loop(DELAY_MILLIS, SCATTER, counter_clockwise);
    CircuitPlayground.clearPixels();
    right_button_pressed = true;
  }
}
