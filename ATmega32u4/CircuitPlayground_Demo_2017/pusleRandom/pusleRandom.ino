#include <Adafruit_CircuitPlayground.h>
#include <Wire.h>
#include <SPI.h>
//variables, r = red, g = green, b = blue, level =  brightness, i = current pixel
int r = 10, g = 100, b = 140, level = 0, i = 0;

void setup() {
  //runs once before the loop and never again
  Serial.begin(9600);
  CircuitPlayground.begin();
  randomSeed(analogRead(0));
}

void loop() {
  //loops continuously
  pulse((int)random(11));
}

void pulse(int x){
  while(level <= 50){
    //increases brightness
    CircuitPlayground.setBrightness(level);
    setPixel(x);
    level += 2;
    delay(50);
  }
  while(level >= 2){
    //decreases brightness
    CircuitPlayground.setBrightness(level);
    setPixel(x);
    level -= 2;
    delay(50);
  }
}

void setPixels(){
  //sets all the pixels, should be run after each change to update them
  for(i = 0; i < 11; i++){
    CircuitPlayground.setPixelColor(i, r, g, b);
  }
}

void setPixel(int p){
  CircuitPlayground.setPixelColor(p, r, g, b);
}


