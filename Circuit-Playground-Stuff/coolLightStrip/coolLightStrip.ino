// Speaker demo for Circuit Playground -- when tapped, plays a very short
// digitized sound sample, very quietly (because teeny tiny speaker).

#include <Adafruit_CircuitPlayground.h>
#include <Adafruit_NeoPixel.h>
#include <Wire.h>
#include <SPI.h>

// Which pin on the Arduino is connected to the NeoPixels?
// On a Trinket or Gemma we suggest changing this to 1
#define PIN            

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS      5
#define HAPTICSPIN     12

int onPixels = 5;

// When we setup the NeoPixel library, we tell it how many pixels, and which pin to use to send signals.
// Note that for older NeoPixel strips you might need to change the third parameter--see the strandtest
// example for more information on possible values.
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, HAPTICSPIN, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel pixels2 = Adafruit_NeoPixel(NUMPIXELS, 6, NEO_GRB + NEO_KHZ800);

int delayval = 250; // delay for half a second
int value;

volatile boolean play = false;

// This function will be called automatically when a tap is detected by the
// accelerometer.  This just sets the global flag 'play' to true, which is
// then detected in loop() (where the sound is then played)...doing heavy
// processing within an interrupt function is sometimes considered poor form.
void myFunction() {
  pixels.clear();
  pixels2.clear();
  if(onPixels < (value/10) and onPixels < 10){
    onPixels++;
  } else if (onPixels > (value/10) and onPixels > 0) {
    onPixels--;
  }
    for(int i=-1;i<onPixels;i++){

      
      
      // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
      if((i&1)==0){
        pixels.setPixelColor(i/2, pixels.Color(205,127, 50)); // blue color.
      }else{
        pixels2.setPixelColor((i-1)/2, pixels.Color(205,127, 50)); // blue color.
      }
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels2.show();

  }
  play = true; // Hey loop(), play the sound!

}


void setup() {
  CircuitPlayground.begin();
  pixels.begin(); // This initializes the NeoPixel library.
  pixels2.begin();


    pixels.clear(); // This sends the updated pixel color to the hardware.
    pixels2.clear();

  for(int i=0;i<NUMPIXELS;i++){

    // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
    pixels.setPixelColor(i, pixels.Color(0,0, 0)); // Moderately bright green color.



  }
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels2.show(); // This sends the updated pixel color to the hardware.
  Serial.begin(9600);

  pixels.setBrightness(30);
  pixels2.setBrightness(30);

  // Configure accelerometer for +-4G range, use the tap interrupt
  // feature to call myFunction() automatically when tapped.
  CircuitPlayground.setAccelRange(LIS3DH_RANGE_4_G);
  CircuitPlayground.setAccelTap(1, 127);
  //attachInterrupt(digitalPinToInterrupt(7), myFunction, RISING);

}

void loop() {
  
  Serial.println(onPixels);
  value = CircuitPlayground.lightSensor();
  if (CircuitPlayground.leftButton() and onPixels >0){
  
  }
    myFunction();
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels2.show();
  /*
  for(int i=-1;i<onPixels;i++){

    // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
    pixels.setPixelColor(i, pixels.Color(0,0, 255)); // blue color.

    pixels.show(); // This sends the updated pixel color to the hardware.

  }\
  */
}
