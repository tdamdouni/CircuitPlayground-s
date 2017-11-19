// Demo for buttons, leds, and switch

//included libraries
#include <Adafruit_CircuitPlayground.h>


uint8_t pixeln = 0; //starting pixel
int r=0, g=0, b=0;    //starting rgb values

//start code, runs only once
void setup() {
  Serial.begin(9600);
  Serial.println("Welcome to Arduino!");

  CircuitPlayground.begin();
}


void loop() {
  // test Red #13 LED
  CircuitPlayground.redLED(HIGH);
  delay(100);
  CircuitPlayground.redLED(LOW);
  delay(100);

  //Switch, when slide to left r=0, otherwise r=255
  if (CircuitPlayground.slideSwitch()) {
    r=0;
  } else {
    r=225;
  }

  //Left Button, changes g value from 0 to 255 and back when pressed
  if (CircuitPlayground.leftButton()) {
    if(g==0){
      g=225; 
    } else{
      g=0;
    }
  }
  
  //R Button, changes b value from 0 to 255 and back when pressed
  if (CircuitPlayground.rightButton()) {
    if(b==0){
      b=225; 
    } else{
      b=0;
    }
  }

  //setting pixels
  CircuitPlayground.setPixelColor(pixeln++, r, g, b);
  if (pixeln == 11) {
    pixeln = 0;
    CircuitPlayground.clearPixels();
  }
}

