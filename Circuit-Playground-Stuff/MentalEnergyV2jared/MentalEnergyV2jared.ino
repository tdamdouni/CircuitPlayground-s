// NeoPixel Ring simple sketch (c) 2013 Shae Erisson
// released under the GPLv3 license to match the rest of the AdaFruit NeoPixel library

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

// Which pin on the Arduino is connected to the NeoPixels?
// On a Trinket or Gemma we suggest changing this to 1
#define PIN            

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS      5
#define HAPTICSPIN     12

// When we setup the NeoPixel library, we tell it how many pixels, and which pin to use to send signals.
// Note that for older NeoPixel strips you might need to change the third parameter--see the strandtest
// example for more information on possible values.
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, HAPTICSPIN, NEO_GRB + NEO_KHZ800);

int delayval = 250; // delay for half a second

int ribbonSensor = 9;
int ribbonSensorValue = 0;
//int thing1;
//int thing2;

int onPixels, offPixels;
int boundedValue = 500;

//int initialTouch = 0;
int lightValues[] = {0,0,0,0,0};

void setup() {
  // This is for Trinket 5V 16MHz, you can remove these three lines if you are not using a Trinket
#if defined (__AVR_ATtiny85__)
  if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
#endif
  // End of trinket special code
  pinMode(ribbonSensor, INPUT_PULLUP);
  pinMode(HAPTICSPIN, OUTPUT);
  Serial.begin(9600);
  onPixels = NUMPIXELS;
  offPixels = 0;
  pixels.begin(); // This initializes the NeoPixel library.
  pixels.setBrightness(30);

  //initialTouch = 0;
  for (int i = 0; i < 5; i++) {
    lightValues[i] = ((1025 / 5) * i);
    //Serial.println("light value " + i + " = " + ((1005/5)*i));
  }
}

void loop() {
  //thing1 = 0;
  //thing2 = 0;
  //Serial.println(offPixels);
  if(offPixels <= 0){offPixels = 0;}
  if(offPixels >= NUMPIXELS){offPixels = NUMPIXELS;}
  
  int currentTouch = analogRead(ribbonSensor);
  delay(20);
  int currentTouch2 = analogRead(ribbonSensor);
  Serial.println(currentTouch);
  Serial.println(currentTouch2);

  
  
  //reset initialTouch and lightValues if no touch happening (currentTouch >= around 1002)
  //set initialTouch and lightValues if currentTouch <= around 1002 && initialTouch == 0

  // For a set of NeoPixels the first NeoPixel is 0, second is 1, all the way up to the count of pixels minus one.
  //ribbonSensorValue = analogRead(ribbonSensor);
  //Serial.println(ribbonSensorValue);
  if(currentTouch - currentTouch2 > 0 && abs(currentTouch-currentTouch2) > 10 && abs(currentTouch-currentTouch2) < 10){
    for (int i = 0; i < 5; i++) {
      if (currentTouch >= lightValues[i]) {
        offPixels++;
      } else if (currentTouch < lightValues[i]) {
        offPixels--;
      }
    }
  }
  pixels.clear(); // This sends the updated pixel color to the hardware.
  

  for(int i=-1;i<offPixels;i++){

    // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
    pixels.setPixelColor(i, pixels.Color(0,0, 255)); // Moderately bright green color.

    pixels.show(); // This sends the updated pixel color to the hardware.

  }
  delay(delayval); // Delay for a period of time (in milliseconds).
}
