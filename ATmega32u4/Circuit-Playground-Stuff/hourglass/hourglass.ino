///////////////////////////////////////////////////////////////////////////////
// Circuit Playground Fading Hourglass
//
// Author: Carter Nelson
// MIT License (https://opensource.org/licenses/MIT)
 
#include <Adafruit_CircuitPlayground.h>
 
#define COUNT_TIME    30000 // milliseconds
#define FADE_STEPS    100   // NeoPixel fade steps
#define R_SAND        255   // Sand color RED value
#define G_SAND        255   // Sand color GREEN value
#define B_SAND        255   // Sand color BLUE value
 
unsigned long DT;
float r, g, b;
float dr, dg, db;
 
///////////////////////////////////////////////////////////////////////////////
void setup() {
  Serial.begin(9600);
  
  // Initialize the Circuit Playground
  CircuitPlayground.begin();
 
  // Compute per NeoPixel wait time
  DT = COUNT_TIME / 10;
  
  // Compute the color value change per fade step
  dr = float(R_SAND) / float(FADE_STEPS);
  dg = float(G_SAND) / float(FADE_STEPS);
  db = float(B_SAND) / float(FADE_STEPS);
}
 
///////////////////////////////////////////////////////////////////////////////
void loop() {
  // Turn ON all the NeoPixels
  for (int p=0; p<10; p++) {
    CircuitPlayground.setPixelColor(p, uint8_t(R_SAND), 
                                       uint8_t(G_SAND), 
                                       uint8_t(B_SAND));
  }
  
  // Loop over each NeoPixel
  for (int p=0; p<10; p++) {
    // Set the start RGB values
    r = float(R_SAND);
    g = float(G_SAND);
    b = float(B_SAND);
    // Loop over each fading step
    for (int n=0; n<FADE_STEPS; n++) {
      delay(DT/FADE_STEPS); // Per fade step delay
      r = r - dr;           // Decrease the red value
      g = g - dg;           //    "      "  green "
      b = b - db;           //    "      "  blue  "
      CircuitPlayground.setPixelColor(p, uint8_t(r),
                                         uint8_t(g),
                                         uint8_t(b));      
    }
  }
  
  // Wait for Circuit Playground to be flipped over (face down)
  while (CircuitPlayground.motionZ() > 0) {};
 
  // A little debounce
  delay(500);
 
  // Wait for Circuit Playground to be flipped back over (face up)
  while (CircuitPlayground.motionZ() < 0) {};
}

