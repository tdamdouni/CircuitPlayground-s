//demo for capacity (touch) sensors, and tones

//included libraries
#include <Adafruit_CircuitPlayground.h>

uint8_t pixeln = 0;         //the starting pixel in the rainbow sequence
int r=255, g=255, b=255;    //the r, g, and b numerical values

//starting code, runs once
void setup(){
  Serial.begin(9600);
  CircuitPlayground.begin();
}

//repeating code, as long as the circuit playground as power this code will repeat
void loop(){
  //for each sensor numbered between 0 and 9 inclusive the corresponding led is turned on when touched
  for(int i=0; i<=9; i++){
    if(CircuitPlayground.readCap(i) > 20){
      CircuitPlayground.setPixelColor(i, r, g, b);
    } else {
      CircuitPlayground.setPixelColor(i,0,0,0);
    }
  }
  
  //sensor 10, plays a tone while touch
  if(CircuitPlayground.readCap(10) > 20){
    CircuitPlayground.playTone(440, 500); //plays a tone at 440 Hz for 500 milliseconds
  }
  
  //sensor 12, when touched makes a rainbow sequence of all 10 pixels
  while(CircuitPlayground.readCap(12) > 20){
    //sets pixeln to colorWheel at 25*pixeln
    CircuitPlayground.setPixelColor(pixeln++, CircuitPlayground.colorWheel(25 * pixeln));
    
    //delays the entire program for 100 milliseconds
    delay(100);
    
    //clears all the pixels and resets pixeln to 0
    if(pixeln==11){
      CircuitPlayground.clearPixels();
      pixeln=0;
    }
  }
  
}

