// Speaker demo for Circuit Playground -- when tapped, plays a very short
// digitized sound sample, very quietly (because teeny tiny speaker).

#include <Adafruit_CircuitPlayground.h>
#include <Wire.h>
#include <SPI.h>

// Enable ONE of these lines to pick a sound to play back when tapped:
//#include "coin.h" // Super Mario coin sound
#include "trek.h" // Star Trek TNG communicator noise

volatile boolean play = false;

const int numNotes = 20;
int saria[] = {
  587,698,880,587,698,880,587,698,880,587,554,587,554,587,784,659,587,659,784,659
};
int noteDurations[] = {
  8,8,4,8,8,4,8,8,8,8,8,8,8,8,8,4,8,8,8,8
};

const int portalNotes = 24;
int portal[] = {
  698,659,587,587,659,784,698,659,587,587,659,262,587,784,587,659,698,587,988,262,587,784,784,659
};
int portalDurations[] = {
  8,8,8,8,4,8,8,8,8,8,8,8,4,8,8,8,8,8,8,4,8,8,4
};



// This function will be called automatically when a tap is detected by the
// accelerometer.  This just sets the global flag 'play' to true, which is
// then detected in loop() (where the sound is then played)...doing heavy
// processing within an interrupt function is sometimes considered poor form.
void myFunction() {
  play = true; // Hey loop(), play the sound!
}

void setup() {
  CircuitPlayground.begin();

  // Configure accelerometer for +-4G range, use the tap interrupt
  // feature to call myFunction() automatically when tapped.
  CircuitPlayground.setAccelRange(LIS3DH_RANGE_4_G);
  CircuitPlayground.setAccelTap(1, 127);
  attachInterrupt(digitalPinToInterrupt(7), myFunction, RISING);
}

void loop() {
  while(!play); // Wait for tap interrupt

  // Play sound data in the audio[] array (declared in one of the .h files).
  // This function "blocks" -- that is, program flow stops until sound is
  // done playing -- it does not play in the background.
  if (CircuitPlayground.slideSwitch()){
    for (int i=0; i<10; ++i) {
      CircuitPlayground.setBrightness(10+(i*20));
      CircuitPlayground.setPixelColor(i, 179-(i*20),68+(i*10), 15);
      delay(100);
    }
 
  }else{
    for (int i=0; i<10; ++i) {
      CircuitPlayground.setBrightness(10+(i*20));    
      CircuitPlayground.setPixelColor(i, 255-(i*20), 0, 100+(i*10));
      delay(100); 
    }
  }
  if (CircuitPlayground.leftButton()){
     for (int thisNote = 0; thisNote < numNotes; thisNote++) { // play notes of the melody
      // to calculate the note duration, take one second divided by the note type.
      //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
      int noteDuration = 1000 / noteDurations[thisNote];
      CircuitPlayground.playTone(saria[thisNote], noteDuration);
 
      // to distinguish the notes, set a minimum time between them.
      //   the note's duration + 30% seems to work well:
      int pauseBetweenNotes = noteDuration * 1.30;
      delay(pauseBetweenNotes);
    }
  }else if (CircuitPlayground.rightButton()){
     for (int thisNote = 0; thisNote < portalNotes; thisNote++) { // play notes of the melody
      // to calculate the note duration, take one second divided by the note type.
      //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
      int noteDuration = 1000 / portalDurations[thisNote];
      CircuitPlayground.playTone(portal[thisNote], noteDuration);
 
      // to distinguish the notes, set a minimum time between them.
      //   the note's duration + 30% seems to work well:
      int pauseBetweenNotes = noteDuration * 1.30;
      delay(pauseBetweenNotes);  
    }
  }else{
    CircuitPlayground.speaker.playSound(audio, sizeof(audio), SAMPLE_RATE);
  }
  //Flash Purple

  //fade in

  //fade out
  if (CircuitPlayground.slideSwitch()){
    for (int i=10; i>-1; i--) {
      for (int temp = i; temp>-1; temp--){
        CircuitPlayground.setBrightness(10+(i*20));
        CircuitPlayground.setPixelColor(i, 179-(i*20),68+(i*10), 15);        
      }
      delay(100);
      CircuitPlayground.clearPixels();
    }
 
  }else{
    for (int i=10; i>-1; i--) {
      for (int temp = i; temp>-1; temp--){
        CircuitPlayground.setBrightness(10+(i*20));    
        CircuitPlayground.setPixelColor(i, 255-(i*20), 0, 100+(i*10));
     }
      delay(100); 
      CircuitPlayground.clearPixels();
    }
  }
  CircuitPlayground.clearPixels();
  
  // Calling speaker.end() after playing a sound is optional -- this will
  // turn off the pin 13 LED (it's connected to a microcontroller pin that's
  // also related to the speaker), but there's a small audible click when it
  // turns off.  Tradeoffs!
  CircuitPlayground.speaker.end();

  play = false; // Clear flag, wait for interrupt
}
