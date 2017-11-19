#include "anima.h"
#define NUM_NEOPIXELS 10

//Constructor
ANIMATION::ANIMATION(uint32_t value){color = value;}
//Destructor
ANIMATION::~ANIMATION(){}

// set color
void ANIMATION::setColor(uint32_t value){
  color = value;
}
//get color
uint32_t ANIMATION::getColor(){
  return color;
}

void ANIMATION::play_circle(int time_val){
  CircuitPlayground.clearPixels();
  CircuitPlayground.setPixelColor(0,color);
  // Loop trhought each pixel turn the previous one off and the current i on
 for (int i=1; i < NUM_NEOPIXELS; i++) {
    delay (time_val);
   CircuitPlayground.setPixelColor((i - 1), 0x000000);
   CircuitPlayground.setPixelColor(i, color);
 } 
}

void ANIMATION::play_blink(int time_val){
  CircuitPlayground.clearPixels();
  for ( int i=1; i < NUM_NEOPIXELS; i++) {
    CircuitPlayground.strip.setPixelColor(i, color);
  }
  // Show all the pixels
  CircuitPlayground.strip.show();
  delay(time_val);
  // Clear all the pixels
  CircuitPlayground.clearPixels();
  delay(time_val);
}

void ANIMATION::play_rainbow(int speed_val) {
  // Make an offset based on the current millisecond count scaled by the current speed.
    uint32_t offset = millis() / speed_val;
    // Loop through each pixel and set it to an incremental color wheel value.
    for(int i=0; i<10; ++i) {
      CircuitPlayground.strip.setPixelColor(i, CircuitPlayground.colorWheel(((i * 256 / 10) + offset) & 255));
    }
    // Show all the pixels.
    CircuitPlayground.strip.show();
}

