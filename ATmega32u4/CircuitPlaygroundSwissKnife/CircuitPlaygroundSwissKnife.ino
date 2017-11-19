#include <Adafruit_CircuitPlayground.h>
#include <Wire.h>
#include <SPI.h>
#include "Adafruit_SleepyDog.h"

#include "Feature.h"
#include "DiceFeature.h"
#include "ClockFeature.h"
#include "SimonFeature.h"

DiceFeature diceFeature;
ClockFeature clockFeature;
SimonFeature simonFeature;

int currentFeature = 0;
Feature* features[] = {
  &clockFeature,
  &simonFeature,
  &diceFeature
};

void setup() {
  Serial.begin(115200);
  Serial.println("Circuit Playground Swiss Knife!");
  CircuitPlayground.begin();
  CircuitPlayground.setAccelRange(LIS3DH_RANGE_8_G);
  CircuitPlayground.setAccelTap(2, TAP_THRESHOLD);
  // Setup tap detection and callback function
  attachInterrupt(digitalPinToInterrupt(7), tapCallback, RISING);
}

void loop() {
  while (!CircuitPlayground.slideSwitch()) {
    CircuitPlayground.clearPixels();
    Watchdog.sleep(1000);
  }
  
  bool leftFirst = CircuitPlayground.leftButton();
  bool rightFirst = CircuitPlayground.rightButton();
  delay(10);

  features[currentFeature]->loop();

  bool leftSecond = CircuitPlayground.leftButton();
  bool rightSecond = CircuitPlayground.rightButton();

  if (leftFirst && !leftSecond) {
    CircuitPlayground.clearPixels();
    currentFeature += 1;
    if (currentFeature >= (sizeof(features)/sizeof(Feature*))) {
      currentFeature = 0;
    }
    features[currentFeature]->startPressed();
    Serial.print("Changed to feature: "); Serial.println(currentFeature, DEC);
  }

  if (rightFirst && !rightSecond) {
    features[currentFeature]->modePressed();
  }
}

void tapCallback() {
  features[currentFeature]->tapDetected();
}
