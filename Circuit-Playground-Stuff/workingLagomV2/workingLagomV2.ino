#include <Adafruit_CircuitPlayground.h>
#include <Wire.h>

static float minTempF[] = {  80.0,  70.0,  -32.0};
static float maxTempF[] = {  85.0,  90.0, 212.0};

// Define color for temp sensor pixels.
#define TEMP_RED    0x00
#define TEMP_GREEN  0x00
#define TEMP_BLUE   0xFF

float lerp(float x, float xmin, float xmax, float ymin, float ymax) {
  if (x >= xmax) {
    return ymax;
  }
  if (x <= xmin) {
    return ymin;
  }
  return ymin + (ymax-ymin)*((x-xmin)/(xmax-xmin));
}

void setup() {
  Serial.begin(9600);
  CircuitPlayground.begin();
}

void loop() {

  // put your main code here, to run repeatedly:
    // Measure the temperatue and use it to light up its LEDs (left half).
    // Reset all lights to off.
    for (int i=0; i<10; ++i) {
      CircuitPlayground.strip.setPixelColor(i, 0);
    }
    
    float tempF = CircuitPlayground.mic.peak(10);
    Serial.println(tempF);
    int level = (int)lerp(tempF, minTempF[mode], maxTempF[mode], 0.0, 5.0);
    for (int i=0; i<level; ++i) {
      CircuitPlayground.strip.setPixelColor(i, TEMP_RED, TEMP_GREEN, TEMP_BLUE);
    }
}

