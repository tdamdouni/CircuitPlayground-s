#ifndef DICEFEATURE_H
#define DICEFEATURE_H

#include "Feature.h"

#define ROLL_THRESHOLD      30          // Total acceleration threshold for roll detect
#define TAP_THRESHOLD       10          // Tap detect threshold
#define DICE_COLOR          0xEA6292    // Dice digits color



class DiceFeature: public Feature {
  
public:
  DiceFeature() {  
  // Seed the random function with noise
  int seed = 0;
  
  seed += analogRead(12);
  seed += analogRead(7);
  seed += analogRead(9);
  seed += analogRead(10);

  randomSeed(seed);

  // Initialize the global states
  newRoll = false;
  rolling = false;
  tapDone = false;
  }
  ~DiceFeature() {}

  virtual void loop() {
    // Compute total acceleration
    X = 0;
    Y = 0;
    Z = 0;
    for (int i=0; i<10; i++) {
      X += CircuitPlayground.motionX();
      Y += CircuitPlayground.motionY();
      Z += CircuitPlayground.motionZ();
      delay(1);
    }
    X /= 10;
    Y /= 10;
    Z /= 10;
  
    totalAccel = sqrt(X*X + Y*Y + Z*Z);
    
    // Check for rolling
    if ((totalAccel > ROLL_THRESHOLD) || tapDone) {
      rollStartTime = millis();
      newRoll = true;
      rolling = true;
      tapDone = false;
    }
    
    // Rolling momentum
    // Keep rolling for a period of time even after shaking has stopped.
    if (newRoll) {
      if (millis() - rollStartTime > 1000) rolling = false;
    }
  
    // Compute a random number from 1 to 6
    rollNumber = random(1,7);
  
    // Display status on NeoPixels
    if (rolling) {
      // Make some noise and show the dice roll number
      CircuitPlayground.playTone(random(400,2000), 20, false);        
      CircuitPlayground.clearPixels();
      for (int p=0; p<rollNumber; p++) {
        CircuitPlayground.setPixelColor(dicePixels[rollNumber-1][p], DICE_COLOR);
      }    
      delay(20);    
    } else if (newRoll) {
      // Show the dice roll number
      newRoll = false;
      CircuitPlayground.clearPixels();
      for (int p=0; p<rollNumber; p++) {
        CircuitPlayground.setPixelColor(dicePixels[rollNumber-1][p], DICE_COLOR);
      }
    }
  }

  virtual void startPressed() {}

  virtual void modePressed() {
    tapDone = true;
  }

  virtual void tapDetected() {
    tapDone = true;  
  }
  
private:
  unsigned long rollStartTime;
  bool rolling;
  bool newRoll;
  bool tapDone;
  uint8_t rollNumber;
  float X, Y, Z, totalAccel;

  uint8_t dicePixels[6][6] = {  // Pixel pattern for dice roll
    { 2, 0, 0, 0, 0, 0 } ,      // Roll = 1
    { 4, 9, 0, 0, 0, 0 } ,      //        2
    { 0, 4, 7, 0, 0, 0 } ,      //        3
    { 1, 3, 6, 8, 0, 0 } ,      //        4
    { 0, 2, 4, 5, 9, 0 } ,      //        5
    { 0, 2, 4, 5, 7, 9 } ,      //        6
  };
};



#endif
