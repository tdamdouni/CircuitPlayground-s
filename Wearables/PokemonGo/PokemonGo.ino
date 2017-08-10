#include <Adafruit_CircuitPlayground.h>
// Variables will change:
int ledState = 0;         // the current state of the output pin
int buttonState;             // the current reading from the input pin
int lastButtonState = LOW;   // the previous reading from the input pin
int ColorState;   // the previous Color set
int R = 0;
int G = 255;
int B = 0;
int Roffset;
int Goffset;
int Boffset;
int FadeDir = 1;
int FadeTurn =0;
int FadeRate = 50;

// the following variables are long's because the time, measured in miliseconds,
// will quickly become a bigger number than can be stored in an int.
long lastDebounceTime = 0;  // the last time the output pin was toggled
long debounceDelay = 50;    // the debounce time; increase if the output flickers
int Sensor;

void setup() {
  CircuitPlayground.begin();
  CircuitPlayground.setBrightness(155);
}

void loop() {
  //CircuitPlayground.lightSensor()
  // read the state of the button into a local variable:
  int reading = CircuitPlayground.rightButton();

  // check to see if you just pressed the button
  // (i.e. the input went from LOW to HIGH),  and you've waited
  // long enough since the last press to ignore any noise:

  // If the switch changed, due to noise or pressing:
  if (reading != lastButtonState) {
    // reset the debouncing timer
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    // whatever the reading is at, it's been there for longer
    // than the debounce delay, so take it as the actual current state:

    // if the button state has changed:
    if (reading != buttonState) {
      buttonState = reading;


      // only toggle the LED if the new button state is HIGH
      if (buttonState == HIGH) {
              ++ledState;
              FadeTurn = 0;
      }
    }
  }
  Sensor = abs(CircuitPlayground.motionX())+abs(CircuitPlayground.motionY())+abs(CircuitPlayground.motionZ());
  if(Sensor>19)ledState=4;

  // set the LED:
  // do something different depending on the
  // range value:
  switch (ledState) {
    case 0:    // your hand is on the sensor
      R = 255;
      G = 0;
      B = 0;
      ColorState=0;
      break;
    case 1:    // your hand is close to the sensor
      R = 255;
      G = 255;
      B = 0;
      ColorState=1;
      break;
    case 2:    // your hand is a few inches from the sensor
      R = 0;
      G = 0;
      B = 255;
      ColorState=2;
      break;
    case 3:    // your hand is nowhere near the sensor
      ledState = 0;
      break;
    case 4:    // your hand is nowhere near the sensor
      ColorFill(255, 255, 255);
      delay(300);
      ColorFill(R/20, G/20, B/20);
      delay(300);
      ledState=ColorState;
      break;
  }
  delay(1);        // delay in between reads for stability
  Roffset=R/FadeRate;
  Goffset=G/FadeRate;
  Boffset=B/FadeRate;
  if (FadeDir){
    FadeTurn++;  
    ColorFill(R-(Roffset*FadeTurn), G-(Goffset*FadeTurn), B-(Boffset*FadeTurn));
    if(FadeTurn>FadeRate){
       FadeDir = 0;
       //FadeTurn = 0;
    }
  } else{
    FadeTurn--;  
    ColorFill(R-(Roffset*FadeTurn), G-(Goffset*FadeTurn), B-(Boffset*FadeTurn));
    if(FadeTurn<1){
       FadeDir = 1;
       //FadeTurn = 0;
    }
  }

  // save the reading.  Next time through the loop,
  // it'll be the lastButtonState:
  lastButtonState = reading;
}

void ColorFill(uint16_t r,uint16_t g,uint16_t b){
  for(uint16_t i=0; i<10; i++) {
    CircuitPlayground.setPixelColor(i, r, g, b);
  }
}
