
#include <Adafruit_NeoPixel.h>
#include <Adafruit_CircuitPlayground.h>
#include <FastLED.h>

#include <Lumineer_LEDAnimation.h>

#define NUM_PIXELS 20
#define PIN 12

// Adjust this number for the sensitivity of the 'click' force
// this strongly depend on the range! for 16G, try 5-10
// for 8G, try 10-20. for 4G try 20-40. for 2G try 40-80
#define CLICKTHRESHHOLD 50

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_PIXELS, PIN, NEO_GRB + NEO_KHZ800);
AnimationController animator = AnimationController(strip);
uint32_t lastAnimationChangeTime = 0;

void setup() {
  // put your setup code here, to run once:
  CircuitPlayground.begin();
  CircuitPlayground.setAccelRange(LIS3DH_RANGE_2_G);
  CircuitPlayground.setAccelTap(1, CLICKTHRESHHOLD);

  // this must go after the CP initialization, otherwise, the strip won't work
  strip.begin();
  animator.SetAnimation(LumineerAnimation_PulseFill);
  
  pinMode(13, OUTPUT);
  digitalWrite(13, LOW);

  Serial.begin(9600);
}

uint32_t lastUpdate = 0;
uint32_t interval = 10000;

void loop() {
  // put your main code here, to run repeatedly:
  if(CircuitPlayground.slideSwitch())
  {
    uint8_t clickState = checkClickState();
    
    if((clickState & 0x5) == 0x5)
    {
      animator.Next();
      lastAnimationChangeTime = millis();
    }
    if((clickState & 0x6) == 0x6)
    {
      animator.Next();
      lastAnimationChangeTime = millis();
    }
  }
  
  uint8_t click = CircuitPlayground.getAccelTap();
  if (click & 0x10)
  {
    animator.Trigger();
  }
  animator.Step();
  
  updateDisplay();
}

void updateDisplay()
{
  LumineerAnimation animation = animator.GetCurrentAnimationType();

  uint16_t pixel = animation % 10;

  uint16_t colorIndex = animation / 10;
  uint32_t color = 0;
  switch(colorIndex)
  {
    case 0:
      color = 0xFF0000;
      break;
    case 1:
      color = 0x00FF00;
      break;
    case 2:
      color = 0x0000FF;
      break;
  }

  CircuitPlayground.strip.clear();

  uint32_t timeSinceLastChange = millis() - lastAnimationChangeTime;

  if(timeSinceLastChange < 5000)
  {
    CircuitPlayground.strip.setPixelColor(pixel, color);
    if(timeSinceLastChange < 2000)
    {
      CircuitPlayground.strip.setBrightness(20);
    }
    else
    {
      timeSinceLastChange -= 2000;
      uint32_t brightness = ((3000 - timeSinceLastChange) * 20) / 3000;
      CircuitPlayground.strip.setBrightness((uint8_t)brightness);
    }
  }

  CircuitPlayground.strip.show();
}

uint8_t checkClickState()
{
  uint32_t longPressTime = 500;
  static uint32_t leftDownTime = 0;
  static uint32_t rightDownTime = 0;
  static bool leftButtonActive = false;
  static bool rightButtonActive = false;
  static bool leftLongPress = false;
  static bool rightLongPress = false;

  static uint16_t leftClicks = 0;
  static uint16_t rightClicks = 0;

  uint8_t clickState = 0;
  uint32_t currentTime = millis();

  if(CircuitPlayground.leftButton())
  {
    if(leftButtonActive == false)
    {
      leftButtonActive = true;
      leftDownTime = currentTime;
      clickState |= 0x5;
    }

    if(!leftLongPress && ((currentTime - leftDownTime) > longPressTime))
    {
      leftLongPress = true;
      leftClicks++;
    }

    if(leftLongPress)
    {
      uint32_t quotient = (currentTime - leftDownTime) / longPressTime;
      if(quotient >= leftClicks)
      {
        leftClicks = quotient+1;
        clickState |= 0x5;
      }
    }
  }
  else
  {
    if(leftButtonActive == true)
    {
      leftLongPress = false;
      leftButtonActive = false;
      leftClicks = 0;
    }
  }

  if(CircuitPlayground.rightButton())
  {
    if(rightButtonActive == false)
    {
      rightButtonActive = true;
      rightDownTime = currentTime;
      clickState |= 0x6;
    }

    if(!rightLongPress && ((currentTime - rightDownTime) > longPressTime))
    {
      rightLongPress = true;
      rightClicks++;
    }

    if(rightLongPress)
    {
      uint32_t quotient = (currentTime - rightDownTime) / longPressTime;
      if(quotient >= rightClicks)
      {
        rightClicks = quotient+1;
        clickState |= 0x6;
      }
    }
  }
  else
  {
    if(rightButtonActive == true)
    {
      rightLongPress = false;
      rightButtonActive = false;
      rightClicks = 0;
    }
  }
  return clickState;
}

