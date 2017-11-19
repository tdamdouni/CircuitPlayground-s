#include <Adafruit_CircuitPlayground.h>

int threshold = 300;  // Threshold for a capacitive touch (higher = less sensitive).
int duration = 100;  // Duration in milliseconds to play a tone when touched.

void setup() {
  CircuitPlayground.begin();
}

void loop() {
  CircuitPlayground.clearPixels();

  int cap0 = CircuitPlayground.readCap(0);
  if (cap0 > threshold) {
    CircuitPlayground.playTone(200, duration);
    CircuitPlayground.setPixelColor(3, 255, 0, 20);
  }
  
  int cap1 = CircuitPlayground.readCap(1);
  if (cap1 > threshold) {
    CircuitPlayground.playTone(300, duration);
    CircuitPlayground.setPixelColor(4, 255, 0, 60);
  }
  
  int cap2 = CircuitPlayground.readCap(2);
  if (cap2 > threshold) {
    CircuitPlayground.playTone(400, duration);
    CircuitPlayground.setPixelColor(1, 255, 0, 100);
  }
  
  int cap3 = CircuitPlayground.readCap(3);
  if (cap3 > threshold) {
    CircuitPlayground.playTone(500, duration);
    CircuitPlayground.setPixelColor(0, 255, 0, 140);
  }
  
  int cap6 = CircuitPlayground.readCap(6);
  if (cap6 > threshold) {
    CircuitPlayground.playTone(600, duration);
    CircuitPlayground.setPixelColor(6, 255, 0, 180);
  }
  
  int cap9 = CircuitPlayground.readCap(9);
  if (cap9 > threshold) {
    CircuitPlayground.playTone(700, duration);
    CircuitPlayground.setPixelColor(8, 255, 0, 220);
  }
  
  int cap10 = CircuitPlayground.readCap(10);
  if (cap10 > threshold) {
    CircuitPlayground.playTone(800, duration);
    CircuitPlayground.setPixelColor(9, 255, 0, 255);
  }
  
  int cap12 = CircuitPlayground.readCap(12);
  if (cap12 > threshold) {
    CircuitPlayground.playTone(900, duration);
    CircuitPlayground.setPixelColor(5, 255, 0, 0);
  }


}
