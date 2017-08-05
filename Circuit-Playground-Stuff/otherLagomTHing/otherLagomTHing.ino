#include <Adafruit_CircuitPlayground.h>
#include <Wire.h>

static int minSound = 5;
static int maxSound = 120;
int counter;
float test;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  CircuitPlayground.begin();
  counter = 19;
}

void loop() {
  // put your main code here, to run repeatedly:
  if (abs(test-CircuitPlayground.mic.peak(100)) > 15){
    for (int i=0; i<5; i++) {
      CircuitPlayground.strip.setPixelColor(i, 0);
    }
  }
    test = CircuitPlayground.mic.peak(100);
    Serial.println(test);
    float level;
    if (test < minSound){
      level = 0;
    } else if (test >= 80){
      level = 5;
    } else if (test >= 50){
      level = 4;
    } else if (test >= 30){
      level = 3;
    } else if (test >= 20){
      level = 2;
    } else if (test >= 10){
      level = 1;
    }
    
    for (int i=0; i<level; i++) {
      CircuitPlayground.strip.setPixelColor(i, 100, 100, 100);
      CircuitPlayground.strip.show();
    }
    delay(100);
    counter++;
    if (counter ==  20){
      CircuitPlayground.playTone(150, 20);
      for (int i=5; i<10; i++) {
        CircuitPlayground.strip.setPixelColor(i, 0);
      }
      for (int i=10; i>random(4,10); i--){
        CircuitPlayground.strip.setPixelColor(i, 255, 0,0);        
      }

      CircuitPlayground.strip.show();
      counter = 0; 
    }
}
