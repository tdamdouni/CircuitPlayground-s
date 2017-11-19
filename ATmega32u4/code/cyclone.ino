#include "Adafruit_CircuitPlayground.h"

static uint8_t pos = 0;
static uint8_t ticks = 0;
static uint8_t score = 10;
static bool lastButtonPos = false;
static bool buttonPos = false;

void playSad();
void playHappy();

void setup() {
  randomSeed(analogRead(0));
  CircuitPlayground.begin();
}

void loop() {
  //if the switch is to the right
  if (!CircuitPlayground.slideSwitch()) {
    CircuitPlayground.clearPixels();
    CircuitPlayground.strip.setPixelColor(pos, CircuitPlayground.colorWheel((pos * 256 / 10) & 255));
    CircuitPlayground.strip.show();
    
    lastButtonPos = buttonPos;
    buttonPos = CircuitPlayground.leftButton();

    if (buttonPos && !lastButtonPos) {
      if (pos == 2) {
        playHappy();
        score += 5;
        pos = random(10);
        ticks = 0;
        return;
      } else {
        score--;
        if (score == 0) {
          playSad();
          score = 10;
          pos = random(10);
          ticks = 0;
          return;
        }
      }
    }

    ticks++;

    if (ticks == 10) {
      ticks = 0;
      pos++;
      if (pos == 10) { 
        pos = 0;
      }
    }

    delay(5 + ((10.0 / score) * 5));
  } else {
    CircuitPlayground.clearPixels();
    for (int i = 0; i < 10; i++) {
      CircuitPlayground.strip.setPixelColor(i, ((score >> i) & 1) * 255, 0, 0);
    }
    CircuitPlayground.strip.show();
    delay(100);
  }
}

void playSad() {
  //D Db C B
  CircuitPlayground.playTone(294, 500);
  delay(550);
  CircuitPlayground.playTone(277, 500);
  delay(550);
  CircuitPlayground.playTone(262, 500);
  delay(550);
  CircuitPlayground.playTone(247, 1000);
  delay(1100);
}

void playHappy() {
  //A Bb B C
  CircuitPlayground.playTone(440, 250);
  delay(260);
  CircuitPlayground.playTone(466, 250);
  delay(260);
  CircuitPlayground.playTone(494, 250);
  delay(260);
  CircuitPlayground.playTone(523, 1000);
  delay(1100);
}
