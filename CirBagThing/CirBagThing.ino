//   ___   _   ___   _____ _  _ ___ _  _  ___ 
//  | _ ) /_\ / __| |_   _| || |_ _| \| |/ __|
//  | _ \/ _ \ (_ |   | | | __ || || .` | (_ |
//  |___/_/ \_\___|   |_| |_||_|___|_|\_|\___|
//
//  Copyright © 2017 Jack Wiberg <768.jac@gmail.com>
//  This program is free software. It comes without any warranty, to
//  the extent permitted by applicable law. You can redistribute it and/or modify it under the
//  terms of the Do What The Fuck You Want To Public License, Version 2,
//  as published by Sam Hocevar. See the COPYING file for more details.

#include <Adafruit_CircuitPlayground.h>
#define CP CircuitPlayground
int brt = 20; //default ljusstyrka
bool mode = 0; //läge
int pmode = 0; //panik-läge
static int totalptrns = 13; //hur många patterns som finns
int curptrn = 0; //vilken pattern man är på
bool refresh = 0; //refresha pattern?
bool justbooted = 1; //sant om pattern ej ändrad än

void setup() {
  Serial.begin(9600); //serial för debugging
  CP.begin(brt); //kör igång cp'n
  if (CP.slideSwitch()) {mode = 0;} else {mode = 1;} //kolla och sätt läge
  if (mode == 0) {sideShow(0,255,0,0);} else {sideShow(1,0,0,255);} //visa ljus på sidorna beroende på läge
}

void loop() {
  if (CP.slideSwitch() != mode) {} else {
    //Falskt = switchen har ändrat plats!!
    CP.clearPixels();
    if (CP.slideSwitch()) {mode = 0;} else {mode = 1;}
    if (mode == 0) {sideShow(0,255,0,0);} else {sideShow(1,0,0,255);}
    pmode = 0;
    CP.redLED(0);
  }
  if (mode == 0) {
    //Switch i vänster position
    if (CP.leftButton()) {nextPattern(); while(CP.leftButton()) {} delay(50);} // Om en knapp är nedtryckt, kör den knappens funktion
    if (CP.rightButton()) {brightnessUp(); while(CP.rightButton()) {} delay(50);} // Sedan vänta på att användaren ska släppa knappen
  } else {                                                                       // Sedan vänta 50 millisekunder för "debounce"
    if (CP.leftButton()) {sosMode(); while(CP.leftButton()) {} delay(50);}
    if (CP.rightButton()) {temperatureMode(); while(CP.rightButton()) {} delay(50);}
  }
}

void nextPattern() {
  CP.clearPixels();
  if (refresh == 0 && justbooted == 0) { //ändra pattern.
    if (curptrn + 1 > totalptrns) {curptrn = 0;} else {curptrn++;}
    Serial.println("Pattern set to");
    Serial.println(curptrn);
    Serial.println("out of");
    Serial.println(totalptrns);
    Serial.println("(zero indexed)");
  } else if (refresh == 0 && justbooted == 1) { //ändra inte pattern om det ej hänt än. egentligen skulle jag bara kunna byta ut detta mot att sätta refresh till 1 på start, men detta är najsare :)
    justbooted = 0;
  } else { //ändra inte pattern om den ska refreshas
    refresh = 0;
    justbooted = 0;
  }
  //BEGIN PATTERN BLOCK!!!
  if (curptrn == 0) { //bob
    sideShow(0,0,255,0);
    sideShow(1,200,0,200);
  }
  if (curptrn == 1) { //några färger 2: electric boogaloo
    CP.setPixelColor(0, 100, 0, 0);
    CP.setPixelColor(1, 200, 0, 0);
    CP.setPixelColor(2, 255, 0, 0);
    CP.setPixelColor(3, 255, 100, 0);
    CP.setPixelColor(4, 255, 200, 0);
    CP.setPixelColor(5, 255, 255, 0);
    CP.setPixelColor(6, 255, 255, 100);
    CP.setPixelColor(7, 255, 255, 200);
    CP.setPixelColor(8, 255, 255, 255);
    CP.setPixelColor(9, 255, 255, 255);
  }
  if (curptrn == 2) { //Gay flagga
    CP.setPixelColor(0, 255, 0, 0);
    CP.setPixelColor(1, 255, 255, 0);
    CP.setPixelColor(2, 0, 255, 0);
    CP.setPixelColor(3, 0, 0, 255);
    CP.setPixelColor(4, 204, 0, 204);
    CP.setPixelColor(5, 204, 0, 204);
    CP.setPixelColor(6, 0, 0, 255);
    CP.setPixelColor(7, 0, 255, 0);
    CP.setPixelColor(8, 255, 255, 0);
    CP.setPixelColor(9, 255, 0, 0);
  }
  if (curptrn == 3) { //Tagen
    sideShow(0,255,0,0);
    sideShow(1,255,0,0);
  }
  if (curptrn == 4) { //Singel
    sideShow(0,0,255,0);
    sideShow(1,0,255,0);
  }
  if (curptrn == 5) { //Gay singel
    sideShow(0,0,255,0);
    CP.setPixelColor(5, 204, 0, 204);
    CP.setPixelColor(6, 0, 0, 255);
    CP.setPixelColor(7, 0, 255, 0);
    CP.setPixelColor(8, 255, 255, 0);
    CP.setPixelColor(9, 255, 0, 0);
  }
  if (curptrn == 6) { //Singel, vill bara ligga ( ͡° ͜ʖ ͡°)
    sideShow(0,0,255,0);
    sideShow(1,0,0,255);
  }
  if (curptrn == 7) { //Bisexual singel
    sideShow(0,0,255,0);
    CP.setPixelColor(5,0, 26, 77);
    CP.setPixelColor(6,0, 26, 77);
    CP.setPixelColor(7,128, 0, 255);
    CP.setPixelColor(8,230, 0, 92);
    CP.setPixelColor(9,230, 0, 92);
  }
  if (curptrn == 8) { //Pansexual singel
    sideShow(0,0,255,0);
    CP.setPixelColor(5,255, 0, 102);
    CP.setPixelColor(6,255, 0, 102);
    CP.setPixelColor(7,255, 255, 0);
    CP.setPixelColor(8,0, 153, 255);
    CP.setPixelColor(9,0, 153, 255);
  }
  if (curptrn == 9) { //straight singel
    sideShow(0,0,255,0);
    CP.setPixelColor(5,0, 51, 204);
    CP.setPixelColor(6,0, 51, 204);
    CP.setPixelColor(7,255, 255, 255);
    CP.setPixelColor(8,255, 0, 102);
    CP.setPixelColor(9,255, 0, 102);
  }
  if (curptrn == 10) { //trans
    CP.setPixelColor(0,102, 204, 255);
    CP.setPixelColor(1,255, 51, 204);
    CP.setPixelColor(2,255, 255, 255);
    CP.setPixelColor(3,255, 51, 204);
    CP.setPixelColor(4,102, 204, 255);
    CP.setPixelColor(5,102, 204, 255);
    CP.setPixelColor(6,255, 51, 204);
    CP.setPixelColor(7,255, 255, 255);
    CP.setPixelColor(8,255, 51, 204);
    CP.setPixelColor(9,102, 204, 255);
  }
  if (curptrn == 11) { //rng
    CP.setPixelColor(0,random(255),random(255),random(255));
    CP.setPixelColor(1,random(255),random(255),random(255));
    CP.setPixelColor(2,random(255),random(255),random(255));
    CP.setPixelColor(3,random(255),random(255),random(255));
    CP.setPixelColor(4,random(255),random(255),random(255));
    CP.setPixelColor(5,random(255),random(255),random(255));
    CP.setPixelColor(6,random(255),random(255),random(255));
    CP.setPixelColor(7,random(255),random(255),random(255));
    CP.setPixelColor(8,random(255),random(255),random(255));
    CP.setPixelColor(9,random(255),random(255),random(255));
  }
  if (curptrn == 12) { //regnbåge (inte gay)
    CP.setPixelColor(0, 255, 0, 0);
    CP.setPixelColor(1, 255, 127, 0);
    CP.setPixelColor(2, 255, 255, 0);
    CP.setPixelColor(3, 0, 255, 0);
    CP.setPixelColor(4, 0, 255, 127);
    CP.setPixelColor(5, 0, 255, 255);
    CP.setPixelColor(6, 0, 0, 255);
    CP.setPixelColor(7, 127, 0, 255);
    CP.setPixelColor(8, 255, 0, 255);
    CP.setPixelColor(9, 255, 0, 127);
  }
  if (curptrn == 13) { //vitt ljus (för ute i mörket typ/ficklampa)
    sideShow(0, 255, 255, 255);
    sideShow(1, 255, 255 ,255);
  }
  //END PATTERN BLOCK!!!
}

void brightnessUp() {
  CP.clearPixels();//cleara alla pixlar
  if (brt == 250) {brt = 0;} else { //om ljusstykan kommer bli över 255, sätt den till 0
    brt = brt + 10; //annars öka den med 10
  }
  CP.setBrightness(brt); //sätt ljusstyrkan
  if (brt >= 250) { sideShow(0, 255, 0 ,0); sideShow(1, 0, 0, 255); delay(500); CP.clearPixels(); }
  refresh = 1; //se till att vi inte byter pattern
  nextPattern(); //ladda om patternen
}

void temperatureMode() {
  pmode = 0;
  CP.clearPixels(); //Stäng av alla pixlar, sätt ljusstyrka till 0.
  CP.setBrightness(0);
  CP.redLED(0);
  delay(25); //Vänta lite
  int temp = CP.temperature(); //Kolla temperatur
  delay(25); //Vänta lite till (Ljus-sensorn kanske plockar upp ljus från lamporna, det vill vi inte!)
  int light = CP.lightSensor();
  Serial.println(light);
  delay(10); //Vänte lite till
  CP.setBrightness(brt); //Sätt tillbaka ljusstyrkan
  if (light >= 600) { //Sätt alla lampor för ljusstyrka
    CP.setPixelColor(9,255,255,255);
  } if (light >= 300) {
    CP.setPixelColor(8,255,255,255);
  } if (light >= 150) {
    CP.setPixelColor(7,255,255,255);
  } if (light >= 75) {
    CP.setPixelColor(6,255,255,255);
  }
  CP.setPixelColor(5,255,255,255);
  //sätt alla lampor för temperatur
  if (temp >= 30) {
    CP.setPixelColor(0,255,0,0);
  } if (temp >= 20) {
    CP.setPixelColor(1,255,255,0);
  } if (temp >= 10) {
    CP.setPixelColor(2,0,255,0);
  } if (temp >= 5) {
    CP.setPixelColor(3,0,255,255);
  }
  CP.setPixelColor(4,0,0,255);
  if (light < 25) {CP.playTone(440, 100, 0);} //om det är typ inget ljus spela en ton
}

void sosMode() {
  pmode++; //Sätt panikläge på eller överfallsalarm
  if (pmode == 1) { //Rengbågsfärger + röd lampa, "Tyst" sos-läge
    CP.clearPixels();
    CP.setBrightness(brt);
    CP.redLED(1);
    CP.setPixelColor(0, 255, 0, 0);
    CP.setPixelColor(1, 255, 127, 0);
    CP.setPixelColor(2, 255, 255, 0);
    CP.setPixelColor(3, 0, 255, 0);
    CP.setPixelColor(4, 0, 255, 127);
    CP.setPixelColor(5, 0, 255, 255);
    CP.setPixelColor(6, 0, 0, 255);
    CP.setPixelColor(7, 127, 0, 255);
    CP.setPixelColor(8, 255, 0, 255);
    CP.setPixelColor(9, 255, 0, 127);
  } while (pmode == 2) { //Röda blinkande lampor, ljud, "Panik" sos-läge. Att man måste reseta grejen för att komma ur läget är en funktion.
    CP.clearPixels();
    CP.setBrightness(255);
    CP.redLED(1);
    CP.playTone(3500, 100, 1);
    sideShow(0,255,0,0);
    sideShow(1,255,0,0);
    delay(10);
  }
  if (pmode == 0) { //Failsafe
    CP.clearPixels();
    CP.setBrightness(brt);
    CP.redLED(0);
  }
}

int sideShow(bool side, int c1, int c2, int c3) {
  if (side == false) {
    CP.setPixelColor(0, c1, c2, c3);
    CP.setPixelColor(1, c1, c2, c3);
    CP.setPixelColor(2, c1, c2, c3);
    CP.setPixelColor(3, c1, c2, c3);
    CP.setPixelColor(4, c1, c2, c3);
  } else {
    CP.setPixelColor(5, c1, c2, c3);
    CP.setPixelColor(6, c1, c2, c3);
    CP.setPixelColor(7, c1, c2, c3);
    CP.setPixelColor(8, c1, c2, c3);
    CP.setPixelColor(9, c1, c2, c3);
  }
}
