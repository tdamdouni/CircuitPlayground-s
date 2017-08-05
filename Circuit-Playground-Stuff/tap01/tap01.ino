
#include <nRF24L01.h>
#include <printf.h>
//#include <RF24.h>
//#include <RF24_config.h>
#include <Adafruit_DRV2605.h>
#include <Adafruit_CircuitPlayground.h>
#include <Wire.h>
#include <SPI.h>

Adafruit_DRV2605 drv;

float press = 0;
float time = 0;
bool available = true;

//COOL COLORS
//12,5,119 (pretty purple)
//86,220,226 (light blue)

void setup() {
  Serial.begin(9600);
  Serial.println("Tap System Ver. 0");

  drv.begin();
  drv.selectLibrary(1);
  drv.setMode(DRV2605_MODE_INTTRIG);
  
  CircuitPlayground.begin();
}

void loop() {
  //AVAILABLE / UNAVAILABLE
  if (CircuitPlayground.slideSwitch()) {
    available = true;
    for (int i = 0; i < 10; i++) {
      CircuitPlayground.setPixelColor(i,0,255,0);
    }
  } else {
    available = false;
    for (int i = 0; i < 10; i++) {
      CircuitPlayground.setPixelColor(i,225,0,0);
    }
  }

  //AVAILABLE & SEND
  if ((CircuitPlayground.leftButton()||CircuitPlayground.rightButton()) && available) {
    for (int i = 0; i < 10; i++) {
        CircuitPlayground.setPixelColor(i,86,220,225);
    }
    drv.setWaveform(0,7);
    drv.setWaveform(1,0);
    drv.go();
  }
  
  CircuitPlayground.setBrightness(5);
}
