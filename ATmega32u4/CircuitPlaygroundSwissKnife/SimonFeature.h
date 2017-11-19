#ifndef SIMONFEATURE_H
#define SIMONFEATURE_H

#include "Feature.h"

#define MAX_SEQUENCE    31
#define NO_BUTTON       -1
#define FAILURE_TONE    100
#define SEQUENCE_DELAY  800
#define GUESS_TIMEOUT   3000
#define DEBOUNCE        250
#define CAP_THRESHOLD   100

struct button {
  uint8_t capPad[2];
  uint8_t pixel[3];
  uint32_t color;
  uint16_t freq;
} simonButton[] = {
  { {3,2},    {0,1,2},  0x00FF00,   415 },  // GREEN
  { {0,1},    {2,3,4},  0xFFFF00,   252 },  // YELLOW
  { {12, 6},  {5,6,7},  0x0000FF,   209 },  // BLUE
  { {9, 10},  {7,8,9},  0xFF0000,   310 },  // RED 
};

class SimonFeature: public Feature {
  
public:
  SimonFeature() {  
    skillLevel = 1;
    randomSeed(millis());
    gameFinished = true;
    startAnimation = true;
  }
  ~SimonFeature() {}

  virtual void loop() {
    
    if (!gameFinished) {
      // Show sequence up to current step
      showSequence();
      
      // Read player button presses
      for (int s=0; s<currentStep; s++) {
        if (!gameFinished) {
          startGuessTime = millis();
          guess = NO_BUTTON;
          while ((millis() - startGuessTime < GUESS_TIMEOUT) && (guess==NO_BUTTON)) {
            guess = getButtonPress();           
          }
          if (guess != simonSequence[s]) {
            gameLost(simonSequence[s]);
          }
        }
        
      }
      if (!gameFinished) {
        currentStep++;
        if (currentStep > sequenceLength) {
          delay(SEQUENCE_DELAY);
          gameWon();
        }
        delay(SEQUENCE_DELAY);
      }
    } else {
      if (startAnimation) {
        indicateButton(3, 300);  // RED
        indicateButton(1, 300);  // YELLOW
        indicateButton(2, 300);  // BLUE
        indicateButton(0, 300);  // GREEN
        startAnimation = false;
      } else {
        CircuitPlayground.clearPixels();
        for (int p=0; p<10 && p<skillLevel; p++) {
          CircuitPlayground.setPixelColor(p, 0x00FFFF);
        }
      }
      
        
    }
  }

  virtual void startPressed() {
    startAnimation = true;
  }

  virtual void modePressed() {
    gameFinished = false;
    newGame();    
    delay(1000);
  }

  virtual void tapDetected() {}
  
  ///////////////////////////////////////////////////////////////////////////////
  void newGame() {
    // Set game sequence length based on skill level
    sequenceLength = (skillLevel * 6);
  
    // Populate the game sequence
    for (int i=0; i<sequenceLength; i++) {
      simonSequence[i] = random(4);
    }
  
    // We start with the first step in the sequence
    currentStep = 1;
    
  }
  
  ///////////////////////////////////////////////////////////////////////////////
  void indicateButton(uint8_t b, uint16_t duration) {
    CircuitPlayground.clearPixels();
    for (int p=0; p<3; p++) {
      CircuitPlayground.setPixelColor(simonButton[b].pixel[p], simonButton[b].color);
    }
    CircuitPlayground.playTone(simonButton[b].freq, duration);
    CircuitPlayground.clearPixels();
  }
  
  ///////////////////////////////////////////////////////////////////////////////
  void showSequence() {
    // Set tone playback duration based on current sequence length
    uint16_t toneDuration;
    if (currentStep<=5) {
      toneDuration = 420;
    } else if (currentStep<=13) {
      toneDuration = 320;
    } else {
      toneDuration = 220;
    }
  
    // Play back sequence up to current step
    for (int i=0; i<currentStep; i++) {
      delay(50);
      indicateButton(simonSequence[i], toneDuration);
    }
  }
  
  ///////////////////////////////////////////////////////////////////////////////
  uint8_t getButtonPress() {
    for (int b=0; b<4; b++) {
      for (int p=0; p<2; p++) {
        if (CircuitPlayground.readCap(simonButton[b].capPad[p]) > CAP_THRESHOLD) {
          indicateButton(b, DEBOUNCE);
          return b;
        }
      }
    }
    return NO_BUTTON;
  }
  
  ///////////////////////////////////////////////////////////////////////////////
  void gameLost(int b) {
    // Show button that should have been pressed
    for (int p=0; p<3; p++) {
      CircuitPlayground.setPixelColor(simonButton[b].pixel[p], simonButton[b].color);
    }
  
    // Play sad sound :(
    CircuitPlayground.playTone(FAILURE_TONE, 1500);

    gameFinished = true;
    currentStep = 0;
    skillLevel = 1;

    delay(GUESS_TIMEOUT);
    
  }
  
  ///////////////////////////////////////////////////////////////////////////////
  void gameWon() {
    // Play 'razz' special victory signal 
    for (int i=0; i<5; i++) {
      indicateButton(3, 100);  // RED
      indicateButton(1, 100);  // YELLOW
      indicateButton(2, 100);  // BLUE
      indicateButton(0, 100);  // GREEN
    }
     
    gameFinished = true;
    currentStep = 0;
    skillLevel++;
  }

private:
  boolean startAnimation;
  uint8_t simonSequence[MAX_SEQUENCE];
  uint8_t skillLevel;
  uint8_t sequenceLength;
  uint8_t currentStep;
  unsigned long startGuessTime;
  int8_t guess;
  boolean gameFinished;
};

#endif

