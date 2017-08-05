// NeoPixel Ring simple sketch (c) 2013 Shae Erisson
// released under the GPLv3 license to match the rest of the AdaFruit NeoPixel library

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

// Which pin on the Arduino is connected to the NeoPixels?
// On a Trinket or Gemma we suggest changing this to 1
#define PIN            6

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS      16
#define HEALTHPIXELS   10
#define STICKERPIXELS  6
#define HAPTICSPIN1 12

// When we setup the NeoPixel library, we tell it how many pixels, and which pin to use to send signals.
// Note that for older NeoPixel strips you might need to change the third parameter--see the strandtest
// example for more information on possible values.
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

int delayval = 250; // delay for half a second
int pressureSensorPin = A9;
int pressureSensorValue =0;

int offPixels =0;


void setup() {
  // This is for Trinket 5V 16MHz, you can remove these three lines if you are not using a Trinket
#if defined (__AVR_ATtiny85__)
  if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
#endif
  // End of trinket special code
  pinMode(pressureSensorPin, INPUT_PULLUP);
  pinMode(HAPTICSPIN1, OUTPUT);
  Serial.begin(9600);
  pixels.begin(); // This initializes the NeoPixel library.
}

void loop() {

  // For a set of NeoPixels the first NeoPixel is 0, second is 1, all the way up to the count of pixels minus one.

  pressureSensorValue = analogRead(pressureSensorPin);

  Serial.println(pressureSensorValue);
  for(int i=0;i<STICKERPIXELS;i++){

    // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
    pixels.setBrightness(16);
    pixels.setPixelColor(i, pixels.Color(255,255,255)); //White
    
    pixels.show(); // This sends the updated pixel color to the hardware.


  }
  if(pressureSensorValue < 100){
    Serial.println("You are coming here");
    offPixels++;
    if(offPixels <=6)
    {
      digitalWrite(HAPTICSPIN1, HIGH);
      delay(200);
      digitalWrite(HAPTICSPIN1, LOW);  
    }
    else{
      digitalWrite(HAPTICSPIN1, HIGH);
      delay(500);
      digitalWrite(HAPTICSPIN1, LOW);
    }
  }
  for(int i=STICKERPIXELS;i<HEALTHPIXELS + STICKERPIXELS - offPixels ;i++){

    // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
    if(offPixels <= 5){
    pixels.setBrightness(16);
    pixels.setPixelColor(i, pixels.Color(0,255,0)); // Res.
    
    pixels.show(); // This sends the updated pixel color to the hardware.

    }
    else{
      pixels.setBrightness(16);
      pixels.setPixelColor(i, pixels.Color(255,0,0));
      
      pixels.show();

    }
  }

  for(int i=HEALTHPIXELS + STICKERPIXELS - offPixels; i < HEALTHPIXELS + STICKERPIXELS;i++){
    pixels.setPixelColor(i,pixels.Color(0,0,0));

    pixels.show();
  }
  delay(delayval);
}
