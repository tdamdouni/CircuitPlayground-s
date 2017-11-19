#include <Adafruit_CircuitPlayground.h>
#include <math.h>

void setup() {
  CircuitPlayground.begin();
}

void loop() {
  int x = CircuitPlayground.motionX();
  int y = CircuitPlayground.motionY();
  if (abs(x) <= 1 && abs(y) <= 1 ) {
    for (int i = 0; i < 10; i++) {
      CircuitPlayground.setPixelColor(i, 150, 150, 150);
    }
  } else {
    double radians = atan2(y, x);
    int degrees = radians * 180 / PI;
    int number = (degrees + 180) / 36;

    for (int i = 0; i < 10; i++) {
      CircuitPlayground.setPixelColor(i, 0, 0, 0);
      CircuitPlayground.setPixelColor(number, 50, number * 10, 150);
    }
  }
  delay(50);

}
