#include <Adafruit_CircuitPlayground.h>

float tempC, tempF;

void setup() {
  Serial.begin(9600);
  CircuitPlayground.begin();
}

void loop() {
  tempC = CircuitPlayground.temperature();
  tempF = CircuitPlayground.temperatureF();

  for (int i=0; i<10; i++){
    CircuitPlayground.strip.setPixelColor(i, (tempF*2), 0, tempF);
  }
  CircuitPlayground.strip.show();


  Serial.print("tempC: ");
  Serial.print(tempC);
  Serial.print("  tempF: ");
  Serial.println(tempF);

  delay(1000);
}
