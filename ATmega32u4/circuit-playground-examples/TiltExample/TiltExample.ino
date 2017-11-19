#include <Adafruit_CircuitPlayground.h>

void setup() {
  CircuitPlayground.begin();
}

void loop() {
  int x = CircuitPlayground.motionX();
  int y = CircuitPlayground.motionY();
  int z = CircuitPlayground.motionZ();

  int red = map(x, -10, 10, 0, 200);
  int green = map(y, -10, 10, 0, 200);
  int blue = map(z, -10, 10, 0, 200);

  for (int i = 0; i < 10; i++) {
    CircuitPlayground.setPixelColor(i, red, green, blue);
  }


}
