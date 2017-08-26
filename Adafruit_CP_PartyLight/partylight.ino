/*
 * Circuit Playground Party Light
 * 
 * version: August 2017
 * Dan Cogliano - zcontent.net
 * 
 * Party light using an Adafruit Circuit Playground and a paper lantern.
 * Use a USB cable to hold CP in the center of lantern. A long USB cable is
 * suggested. Attach an alligator clip between pin 0 (may be changed in code) 
 * and the paper lantern's wire frame to enable the touch interface.
 * 
 * NOTE: Do not let the Circuit Playground touch the paper lantern, the
 * Circuit Playground can get warm. Keep it in the center of the lantern.
 * 
 * The touch interface does the following:
 * Short touch - turn lamp on or change the lamp color to one of 7 colors
 * Long toucn - turn brightness up or down, or turn lantern off 
 * 
 * Letting go while dimming will keep the brightness at that level. A long touch
 * after release will increase the brightness. If held long enough while dimming,
 * the party light will turn off.
 */

#include <Adafruit_CircuitPlayground.h>

// CAPSENSE is pin for capacitive touch
#define CAPSENSE 0

// MAXCAP is the sensitivity of the capacitive touch
#define MAXCAP 100
// # of cycles for long touch
#define LONGTOUCH 50
// # of cycles for a short touch
#define SHORTTOUCH 2
// # brightness increase/decrease per cycle, increase # for faster dimming
#define BRIGHTSTEP 2

static constexpr uint32_t colors[] = 
    { 0xffffff, // white
      0xff0000, // red
      0xff4900, // orange
      0xffff00, // yellow
      0x00ff00, // green
      0x0000ff, // blue
      0xff00ff, // violet/ purple
    };

int colorindex = 0;
int power = false;
uint8_t brightness = 255;
int brightmove = 0 - BRIGHTSTEP;
uint16_t micval = 0;

void setup() {
  //while (!Serial);
  Serial.begin(9600);
  delay(200);
  Serial.println("Circuit Playground Party Light");
  CircuitPlayground.begin();
  CircuitPlayground.clearPixels();
  CircuitPlayground.setBrightness(255);
}

bool checkCapacitiveTouch()
{
  bool touch = false;
  int total = CircuitPlayground.readCap(CAPSENSE);
  if(total > MAXCAP)
  {
    Serial.print("capacitive touch hit: ");
    Serial.println(total);
    return true;
  }
  return false;
}

void powerLight(bool tpower)
{
  if(tpower)
  {
    if(!power)
    {
      power = true;
      Serial.println("light on");
      if(brightness == 0)
      {
        CircuitPlayground.setBrightness(brightness = 255);
        brightmove = 0 - BRIGHTSTEP;        
      }
    }
    for(int i = 0; i < 10; i++)
    {
      CircuitPlayground.setPixelColor(i, colors[colorindex]);
    }
  }
  else
  {
    if(power)
    {
      power = false;
      Serial.println("light off");
    }
    CircuitPlayground.clearPixels();
  }
}


void loop() {
  static bool touch = false;
  static int touching = 0;
  delay(20);
  
  if(checkCapacitiveTouch())
  {
    touch = true;
    touching++;
    if(touching > LONGTOUCH)
    {
      brightness = min(max(brightness + brightmove, 0),255);
      CircuitPlayground.setBrightness(brightness);
      Serial.print("brightness set to ");
      Serial.println(brightness);
      if(brightness == 0)
      {
        powerLight(false);
      }
      else
      {
        powerLight(true);        
      }
    }
  }
  else
  {
    touch = false;
    if(touching > LONGTOUCH)
    {
      brightmove = 0 - brightmove; // change direction
      touching = 0;
      //powerLight(false);
    }
    else if(touching > SHORTTOUCH)
    {
      touching = 0;
      // change color if light is on
      if(power)
      {
        colorindex = (colorindex + 1 ) % (sizeof(colors) / sizeof(uint32_t));
        Serial.print("color index changed to ");
        Serial.println(colorindex);
      }
      powerLight(true);
    }
  }
}
