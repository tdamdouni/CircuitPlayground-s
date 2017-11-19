#ifndef ANIMA_H
#define ANIMA_H

#include <Adafruit_CircuitPlayground.h>

class ANIMATION{
public:
  ANIMATION(uint32_t);
  ~ANIMATION();
  void setColor(uint32_t color);
  uint32_t getColor();
  void play_circle(int time_val);
  void play_blink(int time_val);
  void play_rainbow(int speed_val);
private:
  uint32_t color;
};

#endif

