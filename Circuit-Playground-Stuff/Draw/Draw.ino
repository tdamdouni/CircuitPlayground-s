///////////////////////////////////////////////////////////////////////////////
// Circuit Playground Quick Draw
// 
// Who's faster?
//
// Author: Carter Nelson
// MIT License (https://opensource.org/licenses/MIT)
 
#include <Adafruit_CircuitPlayground.h>
 
#define SHORTEST_DELAY  1000    // milliseconds
#define LONGEST_DELAY   10000   //      "
 
///////////////////////////////////////////////////////////////////////////////
void showOutcome(int player, bool winner) {
  int p1, p2;
  uint32_t color;
 
  // Turn them all off
  CircuitPlayground.clearPixels();
 
  // Set pixel color
  if (winner) {
    color = 0x00FF00;
  } else {
    color = 0xFF0000;
  }
 
  // Set pixel range for player
  switch (player) {
    case 1:
      p1 = 0;
      p2 = 4;
      break;
    case 2:
      p1 = 5;
      p2 = 9;
      break;
    default:
      p1 = 0;
      p2 = 9;
  }
 
  // Show which player won/lost
  for (int p=p1; p<=p2; p++) {
    CircuitPlayground.setPixelColor(p, color);
  }
 
  // Play a little tune
  /*
  if (winner) {
    CircuitPlayground.playTone(800, 200);
    CircuitPlayground.playTone(900, 200);
    CircuitPlayground.playTone(1400, 200);
    CircuitPlayground.playTone(1100, 200);
  } else {
    CircuitPlayground.playTone(200, 1000);
  }
 */
  // Sit here forever
  while (true) {};
}
 
///////////////////////////////////////////////////////////////////////////////
void setup() {
  // Initialized the Circuit Playground
  CircuitPlayground.begin();
 
  // Turn off all the NeoPixels
  CircuitPlayground.clearPixels();
  
  // Seed the random function with noise
  int seed = 0;
  
  seed += analogRead(12);
  seed += analogRead(7);
  seed += analogRead(9);
  seed += analogRead(10);
 
  randomSeed(seed);
 
  // Wait a random period of time
  unsigned long countTime = random(SHORTEST_DELAY, LONGEST_DELAY);
  unsigned long startTime = millis();
  while (millis() - startTime < countTime) {
    // Check if player draws too soon.
    if (CircuitPlayground.leftButton()) showOutcome(1, false);
    if (CircuitPlayground.rightButton()) showOutcome(2, false); 
  } 
  
  // Turn on all the NeoPixels
  for (int p=0; p<10; p++) {
    CircuitPlayground.setPixelColor(p, 0xFFFFFF);  
  }
}
 
///////////////////////////////////////////////////////////////////////////////
void loop() {
  if (CircuitPlayground.leftButton()) showOutcome(1, true);
  if (CircuitPlayground.rightButton()) showOutcome(2, true);
}
