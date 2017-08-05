#include <Adafruit_CircuitPlayground.h>
#include <Arduino.h>
#include "lights.h"

int calculate_actual_pixel(int iteration, int step, Direction direction) {
  int actual_pixel = direction == clockwise ? CIRCUIT_PLAYGROUND_NUMBER_OF_PIXELS - iteration : iteration;
  return (actual_pixel * step) % CIRCUIT_PLAYGROUND_NUMBER_OF_PIXELS;
}

void light_loop(int delay_millis, int step, Direction direction) {
  int pixeln = 0;
  int actual_pixel;
  while (pixeln <= CIRCUIT_PLAYGROUND_NUMBER_OF_PIXELS) {
    actual_pixel = calculate_actual_pixel(pixeln, step, direction);
    CircuitPlayground.setPixelColor(actual_pixel, CircuitPlayground.colorWheel(25 * pixeln));
    delay(delay_millis);
    pixeln++;
  }
}

void pulse(int number_of_pulses, int delay_millis) {
  for (int i=0; i<number_of_pulses; i++) {
    int brightness = 100;
    while (brightness > 0) {
      CircuitPlayground.setBrightness(brightness);
      light_loop(delay_millis, 1, clockwise);
      brightness -= 5;
    }
  }
}
