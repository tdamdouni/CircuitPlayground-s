// https://www.adafruit.com/products/3000
#include <Adafruit_CircuitPlayground.h>
#define COLOR uint32_t
#define arr_len( x )  ( sizeof( x ) / sizeof( *x ) )

COLOR colorChoices[] = {
  0x000000,
  0x111111,
  0x333333,
  0x777777,
  0xBBBBBB,
  0xDDDDDD,
  0xFFFFFF,
  0x400000, // red
  0x900000, // Red
  0xFF0000, // RED!
  0x880088,
  0x0000FF
};
int CLEN = arr_len(colorChoices);
int current = 2;

bool bState[] = { false, false };  // current readings
bool lState[] = { false, false };  // last readings
unsigned long db[] = { 0, 0 };     // debounce timer to track when button state changed
unsigned long debounceDelay = 50;

// Change the color of every pixel
void UpdateColor() {  
  COLOR c = colorChoices[current];
  
  CircuitPlayground.clearPixels();
  // set all
  for (int p=0; p < 10; p++) {
    CircuitPlayground.setPixelColor(p, c);
  }
  CircuitPlayground.strip.show();
}

void Brighter() {
  if (current >= (CLEN - 1)) {
    return;
  }
  
  current++;
  UpdateColor();
}

void Dimmer() {
  if (current < 1) {
    return;
  }

  current--;
  UpdateColor();
}

void setup() {
  /*
  Serial.begin(9600);     
  unsigned long start = millis();
  while (!Serial || (millis() - start) < 1000) {};
  */
  
  CircuitPlayground.begin();
  UpdateColor();
}


bool buttonOn(int idx) {
  bool isOn = (idx == 0) ? 
    CircuitPlayground.leftButton() : 
    CircuitPlayground.rightButton();

  // state has changed, store the time when change was detected
  if (isOn != lState[idx]) {
    db[idx] = millis();
  }

  lState[idx] = isOn;

  // Don't update button state unless it has been in this state 
  // for at least debounceDelay milliseconds
  if ((millis() - db[idx]) > debounceDelay) {
    if (isOn != bState[idx]) {
      // only return updated button state when state has changed. This means 
      // that holding the button down won't continuously send the "on" signal.
      bState[idx] = isOn;
      return isOn;
    }
  }

  // unless debounce and state change requirements are met, 
  // default to "not pressed" status
  return false;
}

void loop() {
  // just wait for input
  if (buttonOn(0)) {    
    Dimmer();
  } else if (buttonOn(1)) {
    Brighter();
  }
}