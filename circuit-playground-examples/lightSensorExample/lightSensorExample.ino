#include <Adafruit_CircuitPlayground.h>

int maxValue = 100;
void setup() {
  CircuitPlayground.begin();
}

void loop() {
  int sensorReading = CircuitPlayground.lightSensor();
  int frequency = map(sensorReading, 0, maxValue, 500, 800);

  Serial.println(sensorReading);

  //CircuitPlayground.playTone(frequency, duration_ms)
  CircuitPlayground.playTone(frequency, 50);
}
