#include <Adafruit_CircuitPlayground.h>

int value;
int oldValue;
int difference;
int p;

void setup() {
  Serial.begin(9600);
  CircuitPlayground.begin();
  p = 0;
}

void loop() {
  value = CircuitPlayground.lightSensor();
  CircuitPlayground.setPixelColor(p, value, 0, (1000/value));  
  p += 1;
  Serial.print("Light Sensor: ");
  Serial.println(value);

  
  if (p == 10){
    p = 0;
  }
  delay(20);
  
}
