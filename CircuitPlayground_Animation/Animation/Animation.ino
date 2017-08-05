#include <Adafruit_CircuitPlayground.h>

#define NUM_NEOPIXELS 10

void setup() {
  Serial.begin(115200);
  CircuitPlayground.begin();
}

void anima_circle(int time, uint32_t color) {
  CircuitPlayground.clearPixels();
  CircuitPlayground.setPixelColor(0, color);
  // Animation
  for ( int i = 1; i < NUM_NEOPIXELS; i++) {
    delay (time);
    CircuitPlayground.setPixelColor((i - 1), 0x000000);
    CircuitPlayground.setPixelColor(i, color);
  }
}

void anima_blink(int time, uint32_t color) {
  CircuitPlayground.clearPixels();
  for ( int i = 1; i < NUM_NEOPIXELS; i++) {
    CircuitPlayground.strip.setPixelColor(i, color);
  }
  CircuitPlayground.strip.show();
  delay(time);
  CircuitPlayground.clearPixels();
  delay(time);
}

void loop() {
  uint32_t  color = 0x0000FF;
  anima_blink(100, color);
}
