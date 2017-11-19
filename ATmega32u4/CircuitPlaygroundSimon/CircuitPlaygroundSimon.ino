//  Simon game for the circuit playground
//
//  Copyright © 2017 Jack Wiberg <768.jac@gmail.com>
//  This program is free software. It comes without any warranty, to
//  the extent permitted by applicable law. You can redistribute it and/or modify it under the
//  terms of the Do What The Fuck You Want To Public License, Version 2,
//  as published by Sam Hocevar. See the COPYING file for more details.

#define CP CircuitPlayground 
#define SR Serial
#include <Adafruit_CircuitPlayground.h>
#include <EEPROM.h>
int wincolor = 0;
bool right[50];
int currentstage = 4;
int done = 0;
int loser = 0;
long int randomseed = 0;

void setup() {
  CP.begin(30);
  randomseed = analogRead(0); 
  CP.setPixelColor(0,0,255,0);
  randomseed = randomseed/CP.motionY(); 
  CP.setPixelColor(1,0,255,0);
  randomseed = randomseed*CP.motionX();
  CP.setPixelColor(2,0,255,0);
  randomseed = randomseed+CP.motionZ();
  CP.setPixelColor(3,0,255,0);
  randomseed = randomseed*CP.temperature();
  CP.setPixelColor(4,0,255,0);
  randomseed = randomseed/CP.temperatureF();
  CP.setPixelColor(5,0,255,0);
  randomseed = randomseed+CP.lightSensor();
  CP.setPixelColor(6,0,255,0);
  randomseed = randomseed-CP.soundSensor(); //Should ensure randomness :)
  CP.setPixelColor(7,0,255,0);
  if (EEPROM.read(137) > 50) {EEPROM.write(137,0);}
  randomSeed(randomseed);
  CP.setPixelColor(8,0,255,0);
  Serial.begin(9600);
  for (int x = 0; x != 50; x++) {
    right[x] = random(0,2);
  }
  CP.setPixelColor(9,0,255,0);
  delay(1000);
}

void loop() {
  done = 0;
  CP.clearPixels();
  for(int x = 0; x != currentstage; x++) {
    if (right[x] == 0) {
      sideShow(0,random(50,255),random(50,255),random(50,255));
      if (currentstage<20) {
      CP.playTone(440,500-currentstage*10,1);
      } else {delay(500-currentstage*10);}
      delay(250-currentstage*3);
      CP.clearPixels();
      delay(30);
    } else {
      sideShow(1,random(50,255),random(50,255),random(50,255));
      if (currentstage<20) {
      CP.playTone(220,500-currentstage*10,1);
      } else {delay(500-currentstage*10);}
      delay(250-currentstage*3);
      CP.clearPixels();
      delay(30-currentstage/2);
    }
  }
  while(done != currentstage) {
    if (CP.leftButton() && right[done] != 0) {
      lose();
      loser = 1;
      break;
    } else if (CP.leftButton() && right[done] == 0) {
      sideShow(0,0,255,0);
      while (CP.leftButton()) {}
      delay(50);
      CP.clearPixels();
      done++;
    }
    if (CP.rightButton() && right[done] != 1) {
      lose();
      loser = 1;
      break;
    } else if (CP.rightButton() && right[done] == 1) {
      sideShow(1,0,255,0);
      while (CP.rightButton()) {}
      delay(50);
      CP.clearPixels();
      done++;
    }
  }
  if (loser == 0) {
    currentstage++;
    delay(250);
    CP.setBrightness(30-currentstage/2);
    } else {
    loser = 0;
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

void lose() {
  if (currentstage > EEPROM.read(137)) {
    EEPROM.write(137, currentstage);
    wincolor = 255;
  } else { wincolor = 0; }
  CP.playTone(4400,500,0);
  sideShow(1,255,0,0);
  sideShow(0,255,0,0);
  if (currentstage>5) {
    CP.setPixelColor(0,wincolor,255,0);
  } if (currentstage>10) {
    CP.setPixelColor(1,wincolor,255,0);
  } if (currentstage>15) {
    CP.setPixelColor(2,wincolor,255,0);
  } if (currentstage>20) {
    CP.setPixelColor(3,wincolor,255,0);
  } if (currentstage>25) {
    CP.setPixelColor(4,wincolor,255,0);
  } if (currentstage>30) {
    CP.setPixelColor(5,wincolor,255,0);
  } if (currentstage>35) {
    CP.setPixelColor(6,wincolor,255,0);
  } if (currentstage>40) {
    CP.setPixelColor(7,wincolor,255,0);
  } if (currentstage>45) {
    CP.setPixelColor(8,wincolor,255,0);
  } if (currentstage>49) {
    CP.setPixelColor(9,wincolor,255,0);
  }
  delay(1000);
  while (CP.rightButton() == 0 && CP.leftButton() == 0) {}
  for (int x = 0; x != 50; x++) {
    right[x] = random(0,2);
  }
  currentstage = 4;
  done = 0;
  delay(250);
}

