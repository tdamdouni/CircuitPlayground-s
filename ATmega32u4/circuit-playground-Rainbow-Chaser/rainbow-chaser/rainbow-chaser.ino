///////////////////////////////////////////////////////////////////////////////
// Circuit Playground Bike Light - Rainbow Chaser
//
// Author: Carter Nelson
// MIT License (https://opensource.org/licenses/MIT)

#include <Adafruit_CircuitPlayground.h>

#define ROTATION_RATE   50    // lower is faster

// Define 10 colors here.
// Must be 10 entries.
// Use 0x000000 if you want a blank space.
uint32_t colors[] = {
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

int colorIndex;
int startIndex;

///////////////////////////////////////////////////////////////////////////////
void setup() {
  CircuitPlayground.begin();
  
  // Make it bright!
  CircuitPlayground.setBrightness(10);

  // Start at the beginning
  startIndex = 0;
}


///////////////////////////////////////////////////////////////////////////////
void loop() {
  // Turn off all the NeoPixels
  CircuitPlayground.clearPixels();

  // Loop through and set pixels
  colorIndex = startIndex;
  for (int pixel=0; pixel<10; pixel++) {
    CircuitPlayground.setPixelColor(pixel, colors[colorIndex]);
    colorIndex++;
    if (colorIndex > 9) colorIndex = 0;
  }

  // Increment start index into color array
  startIndex++;

  // Check value and reset if necessary
  if (startIndex > 9) startIndex = 0;

  // Wait a little bit so we don't spin too fast
  delay(ROTATION_RATE);
}
