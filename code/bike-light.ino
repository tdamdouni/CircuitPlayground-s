///////////////////////////////////////////////////////////////////////////////
// Circuit Playground Bike Light - The All Of Them
// https://learn.adafruit.com/circuit-playground-bike-light/the-all-of-them
// Author: Carter Nelson
// MIT License (https://opensource.org/licenses/MIT)
 
#include <Adafruit_CircuitPlayground.h>
 
// Change these to set speed (lower is faster)
#define FLASH_RATE    250
#define SPIN_RATE     100
#define CYLON_RATE    100
#define BEDAZZLE_RATE 100
#define CHASE_RATE    100
 
// Change these to be whatever color you want
// Use color picker to come up with hex values
#define FLASH_COLOR   0xFF0000
#define SPIN_COLOR    0xFF0000
#define CYLON_COLOR   0xFF0000
 
// Define 10 colors here.
// Must be 10 entries.
// Use 0x000000 if you want a blank space.
uint32_t rainbowColors[] = {
  0xFF0000,   
  0xFF5500,
  0xFFFF00,
  0x00FF00,
  0x0000FF,
  0xFF00FF,
  0x000000,
  0x000000,
  0x000000,
  0x000000
};
 
///////////////////////////////////////////////////////////////////////////////
bool buttonsPressed() {
  return CircuitPlayground.leftButton() | CircuitPlayground.rightButton();  
}
 
///////////////////////////////////////////////////////////////////////////////
void flasher() {
  while (!buttonsPressed()) {
    // Turn on all the pixels to FLASH_COLOR
    for (int pixel=0; pixel<10; pixel++) {
      CircuitPlayground.setPixelColor(pixel, FLASH_COLOR);    
    }
    
    // Leave them on for a little bit  
    delay(FLASH_RATE);
  
    // Turn off all the NeoPixels
    CircuitPlayground.clearPixels();
  
    // Leave them off for a little bit
    delay(FLASH_RATE);
  }
}
 
///////////////////////////////////////////////////////////////////////////////
void spinner() {
  // Can be any two pixels
  int pixel1 = 0;
  int pixel2 = 5;
    
  while (!buttonsPressed()) {
    // Turn off all the NeoPixels
    CircuitPlayground.clearPixels();
  
    // Turn on two pixels to SPIN_COLOR
    CircuitPlayground.setPixelColor(pixel1, SPIN_COLOR);
    CircuitPlayground.setPixelColor(pixel2, SPIN_COLOR);
  
    // Increment pixels to move them around the board
    pixel1 = pixel1 + 1;
    pixel2 = pixel2 + 1;
  
    // Check pixel values
    if (pixel1 > 9) pixel1 = 0;
    if (pixel2 > 9) pixel2 = 0;
  
    // Wait a little bit so we don't spin too fast
    delay(SPIN_RATE);
  }
}
 
///////////////////////////////////////////////////////////////////////////////
void cylon() {
  int pixel1 = 0;
  int pixel2 = 9;
  
  while (!buttonsPressed()) {
    // Scan in one direction
    for (int step=0; step<4; step++) {
      CircuitPlayground.clearPixels();
    
      CircuitPlayground.setPixelColor(pixel1, CYLON_COLOR);
      CircuitPlayground.setPixelColor(pixel2, CYLON_COLOR);
  
      pixel1 = pixel1 + 1;
      pixel2 = pixel2 - 1;
      
      delay(CYLON_RATE);    
    }
  
    // Scan back the other direction
    for (int step=0; step<4; step++) {
      CircuitPlayground.clearPixels();
    
      CircuitPlayground.setPixelColor(pixel1, CYLON_COLOR);
      CircuitPlayground.setPixelColor(pixel2, CYLON_COLOR);
  
      pixel1 = pixel1 - 1;
      pixel2 = pixel2 + 1;
      
      delay(CYLON_RATE);    
    }
  }
}
 
///////////////////////////////////////////////////////////////////////////////
void bedazzler() {
  while (!buttonsPressed()) {
    // Turn off all the NeoPixels
    CircuitPlayground.clearPixels();
  
    // Turn on a random pixel to a random color
    CircuitPlayground.setPixelColor(
      random(10),     // the pixel
      random(256),    // red  
      random(256),    // green
      random(256) );  // blue  
  
    // Leave it on for a little bit
    delay(BEDAZZLE_RATE);
  }
}
 
///////////////////////////////////////////////////////////////////////////////
void rainbow() {
  // Start at the beginning
  int startIndex = 0;
  int colorIndex;
 
  while (!buttonsPressed()) {
    // Turn off all the NeoPixels
    CircuitPlayground.clearPixels();
  
    // Loop through and set pixels
    colorIndex = startIndex;
    for (int pixel=0; pixel<10; pixel++) {
      CircuitPlayground.setPixelColor(pixel, rainbowColors[colorIndex]);
      colorIndex++;
      if (colorIndex > 9) colorIndex = 0;
    }
  
    // Increment start index into color array
    startIndex++;
  
    // Check value and reset if necessary
    if (startIndex > 9) startIndex = 0;
  
    // Wait a little bit so we don't spin too fast
    delay(CHASE_RATE);
  }
}
 
///////////////////////////////////////////////////////////////////////////////
void setup() {
  CircuitPlayground.begin();
  
  // Make it bright!
  CircuitPlayground.setBrightness(255);
}
 
///////////////////////////////////////////////////////////////////////////////
void loop() {
  flasher();    delay(250);
  spinner();    delay(250);
  cylon();      delay(250);
  bedazzler();  delay(250);
  rainbow();    delay(250);
  // TODO: add your animation here!
}