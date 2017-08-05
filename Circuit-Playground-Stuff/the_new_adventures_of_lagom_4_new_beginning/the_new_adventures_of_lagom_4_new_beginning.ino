// Fast Forier Transform Test Program for Circuit Playground
// Mike Barela for Adafruit Industries    September, 2016

#include <Adafruit_CircuitPlayground.h>
#include <Adafruit_NeoPixel.h>
#include <Wire.h>
#include <SPI.h>


#define BINS   32          // The number of FFT frequency bins
#define USABLE 31          // The number of usable FFT frequency bins
#define FRAMES 4           // This many FFT cycles are averaged
#define NUMPIXELS 16       // Number of NeoPixels on NeoPixel Ring
#define HAPTICSPIN 12      // Pin that NeoPixel Ring is attached to

//different NeoPixel offset values for different types of thing to listen for 
int listenForList[] = {1, 1, 3, 2};
// loud person, quiet crowd, loud laughter, cool whistle
int listenFor = 0;   // <- THE VARIABLE THAT DEFINES WHAT WE ARE LISTENING FOR

//pile
int pile;
int pileMax [] = {150, 200, 150, 150}; //different pileMax per listenFor
int fillAmount;

//extra NeoPixel ring
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, HAPTICSPIN, NEO_GRB + NEO_KHZ800);
bool doOnce =false;
int listenForColors[4][3] = {
  {255,0,0},
  {0,0,255},
  {255,127,0},
  {0,255,0}
};
int numberColorBars[] = {
  5,
  5,
  5,
  5
};

//camera flash
const int CapThreshold = 20;
const unsigned long HoldDuration = 75;
unsigned long timeHeld = 0;
boolean flashed = false;
boolean captured = false;

void setup() {
  CircuitPlayground.begin();  // Set up the board library and serial
  Serial.begin(9600);         // Initialize Serial Output
  pixels.begin();
  pixels.setBrightness(80);

  pile = 0;
  fillAmount = 0;
}

void loop() {
  //FFT SHIT
  uint8_t i,j;
  uint16_t spectrum[BINS];     // FFT spectrum output buffer
  uint16_t avg[USABLE];          // The average of FRAME "listens"

  for(j=1; j <= FRAMES; j++) {             // We gather data FRAMES times and average it
     CircuitPlayground.mic.fft(spectrum);  // Here is the CP listen and FFT the data routine
     for(i=0; i < USABLE; i++) {             // Add for an average
       if(spectrum[i] > 255) spectrum[i] = 255; // limit outlier data
       if(i == 0) {
         avg[i] = spectrum[i];
       } else {
         avg[i] = avg[i] + spectrum[i];
       }
     }
  } 
  for(i=0; i < USABLE; i++) {               // For each output bin average
     avg[i] = avg[i] / FRAMES;            //  divide about the number of values aaveraged
  }
  int maxVal = 0, maxIndex = 0;
  for(i=0; i < USABLE; i++) {               // For each output bin average
     if(avg[i] >= maxVal && avg[i] < 339) {               //  find the peak value
       maxVal = avg[i];
       maxIndex = i;                      //  and the bin that max value is in
     }
  }
  for(j=0; j < USABLE; j++) {           // print spectrum 32 bins
     //Serial.print(j); Serial.print(": ");
     //Serial.print(avg[j]);
     //Serial.print(" ");
  }
  //Serial.println("");              // and print the highest value and the bin it is in
  //Serial.print("Max Value = "); Serial.print(maxVal);
  //Serial.print(", Index of Max Value = "); Serial.println(maxIndex);

  //NEOPIXEL && PILE ACCUMULATION SHIT
  //Extra Neopixel
  //Right side
  int lightValue = 255 / 30;
  for (int h = 0; h < 5; h++) {
    int avgNormalized = avg[h + listenForList[listenFor]] - 3;
    
    //switch for listenFor to add to pile
    switch (listenFor) {
      case 0: //loud person
        if (avgNormalized >= 7 && pile < pileMax[listenFor] && CircuitPlayground.readCap(10) > CapThreshold) {pile++;}
      break;
      case 1: //quiet crowd
        if (avgNormalized < 0 && pile < pileMax[listenFor] && CircuitPlayground.readCap(10) > CapThreshold) pile++;
      break;
      case 2: //loud laughter
        if (avgNormalized >= 12 && pile < pileMax[listenFor] && CircuitPlayground.readCap(10) > CapThreshold) pile++;
      break;
      case 3: //cool whistle
        if (avgNormalized >= 7 && pile < pileMax[listenFor] && CircuitPlayground.readCap(10) > CapThreshold) pile++;
      break;
      default:
      break;
    }

    if (listenFor != 1) { //make sure not listening for silence
      if (avgNormalized < 5) avgNormalized = 0;
      int lightAmount = avgNormalized * lightValue;

      int light1 = lightAmount * .5;
      int light2 = lightAmount * .25;
      int light3 = lightAmount * .15;
      if (lightAmount > 255) lightAmount = 255; //PREVENT OVERFLOW EVERY DAY
      if (light2 > 255) light2 = 255;
      if (light1 > 255) light1 = 255;
      if (light3 > 255) light3 = 255;
    
      pixels.setPixelColor(2, lightAmount, lightAmount, lightAmount);
      pixels.setPixelColor(1, light1, light1, light1);
      pixels.setPixelColor(3, light1, light1, light1);
      pixels.setPixelColor(4, light2, light2, light2);
      pixels.setPixelColor(0, light2, light2, light2);
      pixels.setPixelColor(5, light3, light3, light3);
      pixels.setPixelColor(15, light3, light3, light3);
      pixels.show(); // This sends the updated pixel color to the hardware.
    } else {
      int lightAmount;
      if (avgNormalized < 1) {
        lightAmount = 255;
      } else {
        lightAmount = 255/(avgNormalized ^ 2);
      }
      if (lightAmount < 1) lightAmount = 1;
      
      int light1 = (lightAmount * .5)*(.6);
      int light2 = (lightAmount * .25)*(.6);
      int light3 = (lightAmount * .15)*(.6);
      if (lightAmount == 255) light2 = (255*.6);
      if (lightAmount == 255) light1 =(255*.6);
      if (lightAmount == 255) light3 = (255*.6);
    
      pixels.setPixelColor(2, lightAmount, lightAmount, lightAmount);
      pixels.setPixelColor(1, light1, light1, light1);
      pixels.setPixelColor(3, light1, light1, light1);
      pixels.setPixelColor(4, light2, light2, light2);
      pixels.setPixelColor(0, light2, light2, light2);
      pixels.setPixelColor(5, light3, light3, light3);
      pixels.setPixelColor(15, light3, light3, light3);
      pixels.show(); // This sends the updated pixel color to the hardware.
    }
  }

  //left side
  fillAmount = pile / (pileMax[listenFor] / 9);
  /*
  //if (pile <= (pileMax[listenFor] / 5)) fillAmount = 0;
  for (int h = 9; h > 9 - fillAmount; h--) {
    CircuitPlayground.setPixelColor(h, 0, 255, 0);
  }
  */
  for (int h = 6; h < 6 + fillAmount; h++) {
    pixels.setPixelColor(h, listenForColors[listenFor][0], listenForColors[listenFor][1], listenForColors[listenFor][2]);
  }
  pixels.show(); // This sends the updated pixel color to the hardware.

  if (CircuitPlayground.leftButton()){
    listenFor--;
    listenFor = (listenFor < 0) ? 3 : listenFor;
    captured = false;
    Serial.println(listenFor);
    pile = 0;
    pixels.clear();
    flash();
    delay(75);
  }
  if (CircuitPlayground.rightButton()){
    listenFor++;
    listenFor %= 4;
    captured = false;
    Serial.println(listenFor);
    pile = 0;
    pixels.clear();
    flash();
    delay(75);
  }

  if(CircuitPlayground.readCap(9) > CapThreshold){
    if(!flashed){
      if(timeHeld == 0){
        timeHeld = millis();
      }else{
        if(millis() - timeHeld > HoldDuration){
          flash();
          flashed = true;
        }
      }
    }
  }else{
    timeHeld = 0;
    flashed = false;
  }

  if(!captured){
    if(CircuitPlayground.readCap(10) > CapThreshold){
      captured = true;
      pixels.clear();
    }else{
      for (int h = 6; h < 15; h++) {
        pixels.setPixelColor(h, listenForColors[listenFor][0] * .25, listenForColors[listenFor][1] * .25, listenForColors[listenFor][2] * .25);
      }
      pixels.show(); // This sends the updated pixel color to the hardware.*/
    }
  }
}

void flash(){

  for (int p=0; p<10; p++) {
    CircuitPlayground.setPixelColor(p, 0xFFFFFF);
  }
  for (int p=5; p<255; p+=1){
    CircuitPlayground.setBrightness(p);
  }
  CircuitPlayground.clearPixels();
}

