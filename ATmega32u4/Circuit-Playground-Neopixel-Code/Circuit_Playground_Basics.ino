
#include <Adafruit_CircuitPlayground.h>
#include <Wire.h>
#include <SPI.h>
//---------------------
void setup()
{
    Serial.begin(9600);
  Serial.println("Circuit Playground test!");

  CircuitPlayground.begin();
}

void loop()
{
 if (CircuitPlayground.slideSwitch())
 {
CircuitPlayground.redLED(HIGH);
delay(500);
CircuitPlayground.redLED(LOW);
delay(500);
}
else{   
 if (CircuitPlayground.leftButton()&&!CircuitPlayground.rightButton()) {
    CircuitPlayground.playTone(262, 2);
  }
if (CircuitPlayground.rightButton()&&!CircuitPlayground.leftButton()) {
    CircuitPlayground.playTone(523, 2);
  }
  
if(CircuitPlayground.rightButton()&& CircuitPlayground.leftButton())
{
  CircuitPlayground.playTone(350, 2);
}

}
 }



