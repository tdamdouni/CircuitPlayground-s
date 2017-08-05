///////////////////////////////////////////////////////////////////////////////
// Circuit Playground Health Prototype
//
// Author: James Fey using code from Carter Nelson's example
// This Is the Larp Health Prototype
// Materials:
// Circuit Playground by adafruit
// Vibe Motor 
 
#include <Adafruit_CircuitPlayground.h>
#include <Wire.h>
#include <Adafruit_NeoPixel.h>

#define PIN 6
 
uint16_t value;
uint8_t pixels;

bool leftButtonPressed;
bool rightButtonPressed;
int motorState;
long interval;
unsigned long previousMillis = 0;
bool isFighting;
uint32_t fightingLight;
Adafruit_NeoPixel strip = Adafruit_NeoPixel(1, PIN, NEO_GRB + NEO_KHZ800);
uint32_t blue = 0x0000FF;
uint32_t red = 0xFF0000;
 
///////////////////////////////////////////////////////////////////////////////
void setup() {
  Serial.begin(9600);
  value = 1000;
  CircuitPlayground.begin();
  CircuitPlayground.setBrightness(5);
  pinMode(10, OUTPUT);
  interval = 0; 
  motorState = HIGH;
  strip.begin();
  strip.setBrightness(20);
  strip.show(); // Initialize all pixels to 'off'
  digitalWrite(10, motorState);
  fightingLight = blue;
  isFighting = false;
  
}
 
///////////////////////////////////////////////////////////////////////////////
void loop() {
  unsigned long currentMillis = millis();
  leftButtonPressed = CircuitPlayground.leftButton();
  rightButtonPressed = CircuitPlayground.rightButton();
  if (rightButtonPressed and leftButtonPressed){
    if (isFighting == false) {
      isFighting = true;
      fightingLight = red;
    } else {
      isFighting = false;
      fightingLight = blue;
    }
    delay(200);
  }
  strip.setPixelColor(0, fightingLight);
  strip.show();

  
//Check Button and adjust value
  if (rightButtonPressed and !leftButtonPressed and value < 1000){
    CircuitPlayground.playTone(sqrt(value)*10, 50);
    if (!CircuitPlayground.slideSwitch()){
      digitalWrite(10, LOW);
      delay(200);
    }
    value += 100;
    if (!CircuitPlayground.slideSwitch()){
      digitalWrite(10, HIGH);
    }
  }

  if (leftButtonPressed and !rightButtonPressed and value > 0){
    CircuitPlayground.playTone(sqrt(value)*10, 50);
    if (!CircuitPlayground.slideSwitch()){
        digitalWrite(10, LOW);
        delay(200);
    }
    value -= 100;
    if (!CircuitPlayground.slideSwitch()){
      digitalWrite(10, HIGH);
    }
  }

//vibe handling
  if (currentMillis - previousMillis >= interval) {
    // save the last time you blinked the LED
    previousMillis = currentMillis;

    // if the Motor is off turn it on and vice-versa:
    if (motorState == LOW) {
      motorState = HIGH;
    } else {
      motorState = LOW;
      interval = 200;
    }

    // set the motor with the motorState of the variable if switch:
    if (CircuitPlayground.slideSwitch()){
      digitalWrite(10, motorState);
    }
  }

//set function
  pixels = map(value, 0, 1000, 0, 10);
    
  CircuitPlayground.clearPixels();
//Green Lights and high health  
  if (value > 500){
    for (int p=0; p<pixels; p++) {
      CircuitPlayground.setPixelColor(p, 0x00FF00);
    }
    if (motorState == HIGH){
      interval = 1500;
    }
//Yellow Lights and mid Health
  } else if (value > 200 and value < 600) {
    for (int p=0; p<pixels; p++) {
      CircuitPlayground.setPixelColor(p, 0x808000);
    }
    if (motorState == HIGH){
      interval = 2000;
    }
//red lights and low health    
  } else if (value > 0 and value < 300) {
    for (int p=0; p<pixels; p++) {
      CircuitPlayground.setPixelColor(p, 0xFF0000);
    }
    if (motorState == HIGH){
      interval = 2500;
    }
//FLashing red dead
  }else if (value == 0) {
    for (int p=0; p<10; p++) {
      CircuitPlayground.setPixelColor(p, 0xFF0000);
    } 
    delay(100);
    CircuitPlayground.clearPixels();
    delay(100);
    
    }
  delay(100);
}
