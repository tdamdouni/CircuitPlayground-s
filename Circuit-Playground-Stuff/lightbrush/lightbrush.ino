// ---------------------------------------------------------------------------
//Circuit Playground Light Paintbrush
// John Park
// for Adafruit Industries
//
// Use the Circuit Playground as a long exposure photography light paintbrush
// tilt to change color
// adjust brightness with the 10k potentiometer
//
 /*      +X 
 *       __
 *      /  \  
 * +Y  |    |  -Y
 *      \__/
 *      
 *       -X
 */
//
// MIT license, check LICENSE for more information
//
//
// ---------------------------------------------------------------------------

#include <Adafruit_CircuitPlayground.h>
#include <Wire.h>
#include <SPI.h>

int sensorPin = A10;
int sensorValue = 0;
int brightVal = (20);

int X;
int Y;

int red = 0;
int green = 255;
int blue = 0;

void setup() {
  CircuitPlayground.begin();
  CircuitPlayground.clearPixels();
  CircuitPlayground.setBrightness(brightVal);  
}

void loop() {
  sensorValue = analogRead(sensorPin);
  brightVal = map(sensorValue, 0, 1023, 0, 225);

  X = CircuitPlayground.motionX();
  Y = CircuitPlayground.motionY();

  if ( (X>=1) && (Y<1) ) {      //+x, -y = GREEN
    red = 0 ;
    green = 255;
    blue = 0;
  }
  else if ( (X <1 ) && (Y<1) ){ //-x, -y = BLUE
    red = 0;
    green = 0;
    blue = 255;
  }
  else if ( (X >=1) && (Y>=1) ){ //+x, +y = RED
    red = 255;
    green = 0;
    blue = 0;
  }
  else if ( (X <1) && (Y>=1) ){  //-x, +y = YELLOW
    red = 255;
    green = 255;
    blue = 0;
  }

  for (int i=0; i<10; ++i) {
    CircuitPlayground.setBrightness(brightVal);
    CircuitPlayground.strip.setPixelColor(i, red, green, blue);
  }   
  CircuitPlayground.strip.show();
}
