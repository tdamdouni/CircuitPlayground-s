#include <Adafruit_CircuitPlayground.h>

int pixeln = 0, pixelb = 10, b = 10;

void setup(){
  Serial.begin(9600);
  
  CircuitPlayground.begin();
}

void loop(){
  CircuitPlayground.setBrightness(b);
  
  if(CircuitPlayground.leftButton()){
    if(b >=2){
      b-=1;
    } else{
      b=10;
    }
  }
  
  if(CircuitPlayground.rightButton()){
    CircuitPlayground.playTone(760, 200);
  }
  
  if(CircuitPlayground.slideSwitch()){
    if(pixeln != 0){
      CircuitPlayground.clearPixels();
      pixeln=0;
    }
    
    CircuitPlayground.setPixelColor(pixelb--, CircuitPlayground.colorWheel(25*pixelb));
    delay(150);
    Serial.println(pixelb);
    if(pixelb<0){
      pixelb=10;
      CircuitPlayground.clearPixels();
    }
  }else{
    if(pixelb != 10){
      CircuitPlayground.clearPixels();
      pixelb=10;
    }
    
    CircuitPlayground.setPixelColor(pixeln++, CircuitPlayground.colorWheel(25*pixeln));
    delay(150);
    if(pixeln==11){
      pixeln=0;
      CircuitPlayground.clearPixels();
    }
  }
}

