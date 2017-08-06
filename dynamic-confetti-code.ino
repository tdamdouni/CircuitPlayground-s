#include <Adafruit_SleepyDog.h>
#include <FastLED.h>
#include <Adafruit_CircuitPlayground.h>

// uncomment the line below to enable serial debugging output and comment the second line
// bool rgbdebug=true;
bool rgbdebug=false;

#define NUM_LEDS 10
#define DATA_PIN 17

unsigned long last_start;
unsigned int new_led_delay = 6500 / NUM_LEDS;
unsigned int fade_delay = 50;
unsigned int tempLow = 40;
unsigned int tempHi = 75;
CRGB leds[NUM_LEDS];

// dynamic color temperature code part
CRGB colorShift;
CRGB blue = CHSV(HUE_BLUE, 255, 255);
CRGB red = CHSV(HUE_RED, 255, 255);
CRGB white = CRGB::White;
CRGBPalette16 gPal;


void setup()
{
	if (rgbdebug)
	{
		while (!Serial);
		Serial.begin(9600);
		Serial.println("Circuit Playground Dynamic Confetti");
		
	}
	CircuitPlayground.begin();

	gPal =CRGBPalette16(blue,white,red);

	// sanity check delay - allows reprogramming if accidentally blowing power w/leds
	delay(3000);
	FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS).setCorrection(0xB0FFFF);

	// set master brightness to enable FastLED dithering
	FastLED.setBrightness(64);
	last_start = millis();


}

void loop()
{
	while (!CircuitPlayground.slideSwitch()) {
		// Turn off the pixels, then go into deep sleep for a second.
		FastLED.clear();
		FastLED.show();
		Watchdog.sleep(1000);
	}

	fadeToBlackBy( leds, NUM_LEDS, 10);
	if (rgbdebug)
	{
		leds[0] = CHSV(0, 0, 255);
	}
	if (millis() - last_start > new_led_delay)
	{
		int mappedSensor = map (CircuitPlayground.lightSensor(), 0, 1023, 0, 255);
		int constrainedSensor = constrain(mappedSensor, 10, 255);
		int mappedTempF = constrain(map(CircuitPlayground.temperatureF() * 100, tempLow*100, tempHi*100, 0, 255), 0, 240);

		// comment next lint to disable dynamic brightness
		FastLED.setBrightness(constrainedSensor);

		colorShift = ColorFromPalette(gPal, mappedTempF);
		FastLED.setTemperature( colorShift);


		if (rgbdebug)
		{
			Serial.print("Temperature ");
			Serial.print(CircuitPlayground.temperatureF());
			Serial.print(" *F, mapped temp value: ");
			Serial.println(mappedTempF);
		}



		byte x = random16(1, NUM_LEDS);
		if (!leds[x])
		{
			leds[ x ] += CHSV( random8(), random8( 128, 255), 255);
			last_start = millis();
		}
	}
	FastLED.show();
	FastLED.delay(fade_delay);

}
