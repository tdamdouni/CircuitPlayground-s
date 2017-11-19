#ifndef CLOCKFEATURE_H
#define CLOCKFEATURE_H

#include "Feature.h"
#include <TimeLib.h>

#define NO_BUTTON       -1
#define CAP_THRESHOLD   100

struct clockButton {
  uint8_t capPad[2];
} clockButton[] = {
  { {3,2} },
  { {0,1} },
  { {12, 6} },
  { {9, 10} }
};

class ClockFeature: public Feature {
  
public:
  ClockFeature() {  
    mode = 0;
    setTime(11,10,12,23,7,2017);  
    hourColor = CircuitPlayground.strip.Color(random(0, 255), random(0, 255), random(0, 255));
    minuteColor = CircuitPlayground.strip.Color(random(0, 255), random(0, 255), random(0, 255));
    button = NO_BUTTON;
    alarmHour = 0;
    alarmMinute = 0;
  }
  ~ClockFeature() {}

  virtual void loop() {
    if (mode > 0) {
      button = getButtonPress();
      switch (button) {
        case 0:
          switch (mode) {
            case 1:
              adjustTime(3600);
              break;
            case 2:
              alarmHour++;
              if (alarmHour>23) {
                alarmHour = 0;
              }
              break;
          }
          break;
        case 1:
          switch (mode) {
            case 1:
              adjustTime(-3600);
              break;
            case 2:
              alarmHour--;
              if (alarmHour<0) {
                alarmHour = 23;
              }
              break;
          }
          break;
        case 2:
          switch (mode) {
            case 1:
              adjustTime(-60);
              break;
            case 2:
              alarmMinute--;
              if (alarmMinute<0) {
                alarmMinute = 59;
              }
              break;
          }
          break;
        case 3:
          switch (mode) {
            case 1:
              adjustTime(60);
              break;
            case 2:
              alarmMinute++;
              if (alarmMinute>59) {
                alarmMinute = 0;
              }
              break;
          }
          break;
      }
    }
    int mHour = hourFormat12();
    int mMinute = minute();
    if (mode == 2) {
      mHour = alarmHour;
      if (mHour >= 12) {
        mHour = mHour-12;
      }
      mMinute = alarmMinute;
    }
    uint32_t mHourColor = hourColor;
    uint32_t mMinuteColor = minuteColor;
    if (mode == 2) {
      mHourColor = CircuitPlayground.strip.Color(255, 0, 0);
      mMinuteColor = CircuitPlayground.strip.Color(0, 255, 0);
    }
    Serial.println(alarmHour);
    Serial.println(mHour);
    for (int i=0; i<4; i++) {      
      if (((mHour & ( 1 << i )) >> i)==1) {
        CircuitPlayground.strip.setPixelColor(4-i, mHourColor);
      } else {
        CircuitPlayground.strip.setPixelColor(4-i, 0x000000);
      }
    }
    for (int i=5; i<10; i++) {
      if (((mMinute & ( 1 << i-5 )) >> i-5)==1) {
        CircuitPlayground.strip.setPixelColor(i, mMinuteColor);
      } else {
        CircuitPlayground.strip.setPixelColor(i, 0x000000);
      }
    }  
    if (((mMinute & ( 1 << 5 )) >> 5)==1) {
      CircuitPlayground.strip.setPixelColor(0, mMinuteColor);
    } else {
      CircuitPlayground.strip.setPixelColor(0, 0x000000);
    }
    CircuitPlayground.strip.show();
    if (mode == 0) {
      delay(1000);
    } else {
      delay(100);
    }
  }

  virtual void startPressed() {}

  virtual void modePressed() {
    mode += 1;
    if (mode > 2) {
      mode = 0;
    }
  }

  virtual void tapDetected() {}

 uint8_t getButtonPress() {
    for (int b=0; b<4; b++) {
      for (int p=0; p<2; p++) {
        if (CircuitPlayground.readCap(clockButton[b].capPad[p]) > CAP_THRESHOLD) {
          return b;
        }
      }
    }
    return NO_BUTTON;
  }
  
 private:
  int mode;
  int8_t button;
  uint32_t hourColor;
  uint32_t minuteColor;
  int alarmHour;
  int alarmMinute;
};

#endif

