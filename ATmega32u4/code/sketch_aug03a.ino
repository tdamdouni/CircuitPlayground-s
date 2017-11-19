#include <Adafruit_CircuitPlayground.h>

void setup() {
  // put your setup code here, to run once:
  CircuitPlayground.clearPixels();
  CircuitPlayground.temperature();
  CircuitPlayground.lightSensor();
  CircuitPlayground.soundSensor();
  CircuitPlayground.redLED(true);
  CircuitPlayground.setPixelColor(1, 255, 255, 0);
  CircuitPlayground.setBrightness(155);
  CircuitPlayground.playTone(440, 500);
}

void loop() {
  // put your main code here, to run repeatedly:

}
