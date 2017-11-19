#include <SPI.h>
#include <Wire.h>
#include <Adafruit_CircuitPlayground.h> 

/*
The Circuit Playground Dice Bag  - CC Attribution-ShareAlike 4.0 International Tom Higgins & Sons 

TO select the type of die you would like to throw 
  First put the Select Switch in the proper position
  Then press the proper Button


You can hold down the Button and it will flash through many tosses.
Release the Button and your results will show on the Circuit Playground as 
two (or one) lit NeoPixel

Red=Tens Place (0-9)
Blue=Ones Place (0-9)
Green=Tens and Ones are the same (00,11,22,33,44,55,66,77,88,99)

The NeoPixels are arranged from 0 - 9 . If you are holding your Circuit Playground with the USB port facing Up

0 is the top left NeoPixel closest to the USB port
1 is to the left of that
..
4 is the bottom let NeoPixel closest to the Battery Jack
5 is the bottom right NeoPixel closest to the Battery Jack
..
9 is the top tight NeoPixel closest to the USB port


*/

int troll = 0;
int ones = 0;
int tens = 0;


void setup()
{
	Serial.begin(9600);
	randomSeed(analogRead(0));
    CircuitPlayground.begin();
}

void loop()
{
	CircuitPlayground.setBrightness((CircuitPlayground.lightSensor()+4)/4);         //variable neopixel birghtness based on current light level
if (CircuitPlayground.slideSwitch()) {
	if (CircuitPlayground.leftButton()) {tossd100();}
	if (CircuitPlayground.rightButton()) {tossd20();}
      }
else	
	{
	if (CircuitPlayground.leftButton()) {tossd12();}
	if (CircuitPlayground.rightButton()) {tossd06();}
	}
}

void tossd100() {                                         // function for d100
	troll = random(0,99);
    prepthrow(troll);
}

void tossd20() {                                          // function for d20
	troll = random(1,21);
    prepthrow(troll);

}

void tossd12() {                                          // function for d12
	troll = random(1,13);
    prepthrow(troll);
}

void tossd06() {	                                      // function for d6
	troll = random(1,7);
    prepthrow(troll);
}

void prepthrow(int troll) {                               // function to take the roll and parse it to tens and ones
	Serial.println(" ");                                  // print throw results to the console
	Serial.print("Throw was a ");
	Serial.print(troll);
    ones=troll % 10;
    tens=troll / 10;
	showtoss(ones,tens);
   }


void showtoss(int ones,int tens) {                         // function to display the results on the neopixels  
	Serial.print("  tens-");                              // print the tens and ones breakdown to console
	Serial.print(tens);
	Serial.print("  ones-");
	Serial.print(ones);
	CircuitPlayground.clearPixels();
	CircuitPlayground.playTone((ones*100)+1, 50);         // attemped to make it sound like dice being rolled
	if (ones==tens){
	CircuitPlayground.setPixelColor(tens, 5, 255, 5);     // if ones and tens are the same show as green
	
	}
	else {
	CircuitPlayground.setPixelColor(ones, 5, 5, 255);     // show ones as blue    
	CircuitPlayground.setPixelColor(tens, 255, 5, 5); }   // show tens as red
}
