#include <Adafruit_CircuitPlayground.h>
#include "anima.h"

ANIMATION anima(0x0000FF);
  
void setup() {
  Serial.begin(115200);
  CircuitPlayground.begin();
}

void loop() {
 // anima.play_rainbow(5);
  anima.play_circle(100);
}
