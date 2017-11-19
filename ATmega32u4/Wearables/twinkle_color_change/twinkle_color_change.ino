#include <Wire.h>
#include "Adafruit_TCS34725.h"
#include <Adafruit_NeoPixel.h>

#define PIN 6
#define colorButton 9
#define motion 10

// Parameter 1 = number of pixels in strip
// Parameter 2 = pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(20, PIN, NEO_GRB + NEO_KHZ800);

  // Starting values of each color befor they fade.
  int rBase = 150;
  int gBase = 200;
  int bBase = 30;
  // Initiolizing the memory for each of the 20 LEDs
  int rMemo[] = {0, 0, 0, 0, 0 ,0, 0, 0, 0, 0 ,0, 0, 0, 0, 0 ,0, 0, 0, 0, 0};
  int gMemo[] = {0, 0, 0, 0, 0 ,0, 0, 0, 0, 0 ,0, 0, 0, 0, 0 ,0, 0, 0, 0, 0};
  int bMemo[] = {0, 0, 0, 0, 0 ,0, 0, 0, 0, 0 ,0, 0, 0, 0, 0 ,0, 0, 0, 0, 0};
  // Initiolizing the temporary RGB values
  int red = 0;
  int green = 0;
  int blue = 0;
  
  // How quickly the pixles fade (rBace/fade)
  int fade = 30;
  int thisFade = 0;
  
long randNumber;
  int twinkle = 2;

// our RGB -> eye-recognized gamma color
byte gammatable[256];
Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);


void setup() {
  pinMode(colorButton, INPUT);
  pinMode(motion, INPUT);
  digitalWrite(colorButton, HIGH);
  digitalWrite(motion, HIGH);
  
  Serial.begin(9600);
  Serial.println("Color View Test!");
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
  delay(1000);
  
  if (tcs.begin()) {
    Serial.println("Found sensor");
  } else {
    Serial.println("No TCS34725 found ... check your connections");
    while (1); // halt!
  }
  
  // thanks PhilB for this gamma table!
  // it helps convert RGB colors to what humans see
  for (int i=0; i<256; i++) {
    float x = i;
    x /= 255;
    x = pow(x, 2.5);
    x *= 255;
      
    gammatable[i] = x;      
    //Serial.println(gammatable[i]);
  }
  colorPick();
} 
  
void loop() {
  // if the user pushes the Trigger button and lets go, then start transmission of all POWER codes
  if (digitalRead(colorButton) == 0) {
    colorPick();
  }
  if (digitalRead(motion) == 0) {
    twinkle = 250;
  } else {
    twinkle = 2;
  }
  for(uint16_t i=0; i<strip.numPixels(); i++) {
    //Load the last RGB values for this pixle 
    red = rMemo[i];
    green = gMemo[i];
    blue = bMemo[i];
// Make the fade adjustment for each color of this pixle
    if (red > 0) { 
      thisFade = rBase / fade;
      if (thisFade == 0) {thisFade = 1;}
      red = red - thisFade;
      if (red < 0) {red = 0;}
      rMemo[i] = red;
    }
    if (green > 0) {
      thisFade = gBase / fade;
      if (thisFade == 0) {thisFade = 1;}
      green = green - thisFade;
      if (green < 0) {green = 0;}
      gMemo[i] = green;
     }
    if (blue > 0) {
      thisFade = bBase / fade;
      if (thisFade == 0) {thisFade = 1;}
      blue = blue - thisFade; 
      if (blue < 0) {blue = 0;}
      bMemo[i] = blue;
      }
      Serial.print("\n pixle["); Serial.print(i);Serial.print("]"); Serial.print("= r"); Serial.print(red);Serial.print(", g"); Serial.print(green);Serial.print(", b"); Serial.print(blue);
    uint32_t c = strip.Color(red, green, blue);
    
    strip.setPixelColor(i, c);
    strip.show();
    randNumber = 250;
    //}
    randNumber = random(500);
    if (randNumber < twinkle) { 
    Serial.print("\n pixle["); Serial.print(i);Serial.print("]"); Serial.print("= r"); Serial.print(rBase);Serial.print(", g"); Serial.print(gBase);Serial.print(", b"); Serial.print(bBase); Serial.print(" ---- BLINK");
    uint32_t c = strip.Color(rBase, gBase, bBase); 
    rMemo[i] = rBase;
    gMemo[i] = gBase;
    bMemo[i] = bBase;
    strip.setPixelColor(i, c);
    strip.show();
  }
    delay(1);
    
  }
  //delay(0);
}

void colorPick() {
for (int i=0; i<3; i++){ //this sequence flashes the first pixel three times as a countdown to the color reading.
    strip.setPixelColor (19, strip.Color(188, 188, 188)); //white, but dimmer-- 255 for all three values makes it blinding!
    strip.show();
    delay(1000);
    strip.setPixelColor (19, strip.Color(0, 0, 0));
    strip.show();
    delay(500);
  }
  
  uint16_t clear, red, green, blue;
 
  tcs.setInterrupt(false);      // turn on LED
 
  delay(60);  // takes 50ms to read 
  
  tcs.getRawData(&red, &green, &blue, &clear);
 
  tcs.setInterrupt(true);  // turn off LED
  
  Serial.print("C:\t"); Serial.print(clear);
  Serial.print("\tR:\t"); Serial.print(red);
  Serial.print("\tG:\t"); Serial.print(green);
  Serial.print("\tB:\t"); Serial.print(blue);
 
  // Figure out some basic hex code for visualization
  uint32_t sum = red;
  sum += green;
  sum += blue;
  sum = clear;
  float r, g, b;
  r = red; r /= sum;
  g = green; g /= sum;
  b = blue; b /= sum;
  r *= 256; g *= 256; b *= 256;
  Serial.print("\t");
  Serial.print((int)r, HEX); Serial.print((int)g, HEX); Serial.print((int)b, HEX);
  Serial.println();
 
  Serial.print((int)r ); Serial.print(" "); Serial.print((int)g);Serial.print(" ");  Serial.println((int)b );
  //colorWipe(strip.Color(gammatable[(int)r], gammatable[(int)g], gammatable[(int)b]), 0);
  
  rBase = gammatable[(int)r];
  gBase = gammatable[(int)g];
  bBase = gammatable[(int)b];
  
  for(uint16_t i=0; i<strip.numPixels(); i++) {
    rMemo[i] = rBase;
    gMemo[i] = gBase;
    bMemo[i] = bBase;
    Serial.print("\nSTART--- r"); Serial.print(i); Serial.print("="); Serial.print(rMemo[i]);Serial.print(" g"); Serial.print(i); Serial.print("="); Serial.print(gMemo[i]);Serial.print(" b"); Serial.print(i); Serial.print("="); Serial.print(bMemo[i]);
    uint32_t c = strip.Color(rMemo[i], gMemo[i], bMemo[i]); 
    strip.setPixelColor(i, c);
    strip.show();
    delay(10);
  }
}
