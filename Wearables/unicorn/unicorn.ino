#include <Adafruit_NeoPixel.h>

#define PIN 5 //alt pin 6
#define Button 4 //alt pin 9

// Parameter 1 = number of pixels in strip
// Parameter 2 = pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(60, PIN, NEO_GRB + NEO_KHZ800);
float waitTime = 50.0;
int var = 0;
int flash = 0;
int Twinkle = 1;
int buttonState = 0;         // variable for reading the pushbutton status
uint8_t Bright = 105;
uint8_t LightB = 0;
uint8_t LEDr;
uint8_t LEDg;
uint8_t LEDb;

void setup() {
  //LightUp = map(LightUp, LightB, Bright, 1, 255);
  //LightDown = map(LightDown, LightB, 255, LightB, Bright);
   Serial.begin(9600);
   // initialize the pushbutton pin as an input:
    pinMode(Button, INPUT);
  digitalWrite(Button, HIGH);
  strip.begin();
  strip.setBrightness(Bright); //adjust brightness here
  strip.show(); // Initialize all pixels to 'off'
}

void loop() {
  // Some example procedures showing how to display to the pixels:
  if (flash == 0 ) {
    waitTime = 50;
    var = 0;
  while(waitTime > 1){
    colorWipe(strip.Color(255, 255, 255), waitTime); // Red
    colorWipe(strip.Color(0, 0, 0), waitTime); // Red
    waitTime = (float)waitTime - ((float)waitTime / 4);
  }
  waitTime = 100;
  while(var < 40){
    flashWipe(strip.Color(255, 255, 255), waitTime); // Red
    flashWipe(strip.Color(0, 0, 0), waitTime); // Red
    waitTime = (float)waitTime - ((float)waitTime / 30);
    var++;
  }
  rainbowCycle(20);

    flash = 1;
    //flashWipe(strip.Color(234, 12, 153), waitTime); // Red
  }
    // read the state of the pushbutton value:
  buttonState = digitalRead(Button);

  // check if the pushbutton is pressed.
  // if it is, the buttonState is HIGH:
  if (buttonState == LOW) {     
    // turn LED on:    
    flash = 0;
  }
  FadeLight(5);
}

// Fill the dots one after the other with a color
void colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, c);
      strip.show();
      delay(wait);
  }
}

void flashWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
     strip.setPixelColor(i, c);
  }
     strip.show();
     delay(waitTime);
}

// Slightly different, this makes the rainbow equally distributed throughout
void rainbowCycle(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256*4; j++) { // 5 cycles of all colors on wheel
    for(i=0; i< strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  if(WheelPos < 85) {
   return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  } else if(WheelPos < 170) {
   WheelPos -= 85;
   return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } else {
   WheelPos -= 170;
   return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
}

void FadeLight(uint8_t wait) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
if (random(3000) < Twinkle) {
  if (Twinkle < 30) {
    Twinkle++;
  }
      LEDr = 255;
      LEDg = 255;
      LEDb = 255;
} else {
      LEDr =(strip.getPixelColor(i) >> 16);
      LEDg =(strip.getPixelColor(i) >> 8);
      LEDb =(strip.getPixelColor(i));
      LEDr = map(LEDr, 0, Bright, 0, 255);
      LEDg = map(LEDg, 0, Bright, 0, 255);
      LEDb = map(LEDb, 0, Bright, 0, 255);
        if(LEDr > LightB) {
          LEDr = LEDr-((LEDr - LightB)/10);
        }else{
          LEDr = LightB;
        }
        if(LEDg > LightB) {
          LEDg = LEDg-((LEDg - LightB)/10);
        }else{
          LEDg = LightB;
        }
        if(LEDb > LightB) {
          LEDb = LEDb-((LEDb - LightB)/10);
        }else{
          LEDb = LightB;
        }
}
     strip.setPixelColor(i, LEDr, LEDg, LEDb);
     strip.show();
       }
}
