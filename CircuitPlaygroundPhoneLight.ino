#include <Adafruit_CircuitPlayground.h>
#include <Wire.h>
#include <SPI.h>

#define BLINKY 13

// Threshold for a capacitive touch (higher = less sensitive).
#define CAP_THRESHOLD  100
// Number of samples to take for a capacitive touch read.
#define CAP_SAMPLES     40
// number of brightness levels
#define MAXBRIGHT       64

int brightness = MAXBRIGHT/10;
int currentColor = 0;
int currentPattern = 0;
int currentBiColor = 0;
int ordreBicolor = 0;
int colorState = 0;
// LED patterns (which ones are on or off)
const String patterns[] = {
	"1111111111",
	"1101111011",
	"1000110001",
	"0101001010",
	"1010110101",
	"1111100000",
	"0000011111",
	"0011111100",
	"1110000111",
};
int NPATTERNS = sizeof(patterns)/sizeof(patterns[0]);
// Color names
#define Black   0x000000
#define White   0xFFFFFF
#define Red     0xFF0000
#define Green   0x00FF00
#define Blue    0x0000FF
#define Yellow  0xFFFF00
#define Magenta 0xFF00FF
#define Cyan    0x00FFFF
// Colors for the one-color mode
const uint32_t colors[] = {
	White,
	// couleurs primaires
	Red,
	Green,
	Blue,
	// couleurs complémentaires
	Yellow,
	Magenta,
	Cyan,
};
int NCOLORS = sizeof(colors)/sizeof(colors[0]);
//
struct BiCol {
	uint32_t left;
	uint32_t right;
};
// Colors for the two-color mode
const BiCol biColors[] = {
	// primary colors
	{ Red, Green },
	{ Green, Blue },
	{ Blue, Red },
	// complementary colors
	{ Red, Cyan },
	{ Blue, Yellow },
	{ Green, Magenta },
	// other colors together
	{ Yellow, Magenta },
	{ Magenta, Cyan },
	{ Cyan, Yellow },
	// everything else
	{ Blue, Cyan },
	{ Red, Magenta },
	{ Green, Cyan },
	{ Red, Yellow },
	{ Blue, Magenta },
	{ Green, Yellow },
};
int NBICOLORS = sizeof(biColors)/sizeof(biColors[0]);
// convert the brightness level
int getBrightness() {
	uint32_t bright;
	bright = (255L*brightness*brightness)/(MAXBRIGHT*MAXBRIGHT);
	bright = max(0,min(255,bright));
	return bright;
}
// Set the colors of the Neopixels according to the current state
// brightness/currentColor/currentPattern
// One color for all
void doLightState() {
	uint32_t color = colors[currentColor];
	// light up the red LED if max brightness
	if(brightness == MAXBRIGHT) {
		CircuitPlayground.redLED(HIGH);
	} else {
		CircuitPlayground.redLED(LOW);
	}
	// set the brightness and the colors
	CircuitPlayground.setBrightness(getBrightness());
	for(int pixeln = 0; pixeln < 10; pixeln++) {
		if(patterns[currentPattern][pixeln] == '1') {
			CircuitPlayground.setPixelColor(pixeln, color);
		} else {
			CircuitPlayground.setPixelColor(pixeln, Black);
		}
	}
}
// Set the colors of the Neopixels according to the current state
// brightness/currentBiColor/currentPattern
// One color for each side
void doBiLightState() {
	uint32_t color,left,right;
	// swap colors left/right
	if(ordreBicolor) {
		left = biColors[currentBiColor].right;
		right = biColors[currentBiColor].left;
	} else {
		right = biColors[currentBiColor].right;
		left = biColors[currentBiColor].left;
	}
	// light up the red LED if max brightness
	if(brightness == MAXBRIGHT) {
		CircuitPlayground.redLED(HIGH);
	} else {
		CircuitPlayground.redLED(LOW);
	}
	// set the brightness and the colors
	CircuitPlayground.setBrightness(getBrightness());
	for(int pixeln = 0; pixeln < 10; pixeln++) {
		// alternate colors left/right
		if(pixeln<5) color = right;
		else color = left;
		if(patterns[currentPattern][pixeln] == '1') {
			CircuitPlayground.setPixelColor(pixeln, color);
		} else {
			CircuitPlayground.setPixelColor(pixeln, Black);
		}
	}
}
//


void setup() {
	//while (!Serial);
	Serial.begin(9600);
	Serial.println("Circuit Playground test!");
	CircuitPlayground.begin(255);
	doLightState();
}

// 
enum ButtonStatus {
	BUTTONS_OFF,
	BTNLEFT,
	BTNRIGHT,
	CAPCOLOR,
	CAPMODE,
	CAPBRIGHTUP,
	CAPBRIGHTDOWN,
};
ButtonStatus buttonStatus = BUTTONS_OFF;
void loop() {
	// slide switch: turn off the thingies
	if(CircuitPlayground.slideSwitch()) {
		for(int pixeln = 0; pixeln < 10; pixeln++) {
			CircuitPlayground.setPixelColor(pixeln, 0, 0, 0);
		}
		delay(100);
		return;
	}
	// cap: 12   1
	//    6        0
	//    9        2
	//      10   3
	//
	// register the buttons pressed or touched
	ButtonStatus newStatus = BUTTONS_OFF;
	if(CircuitPlayground.leftButton()
	|| CircuitPlayground.readCap(10, CAP_SAMPLES) >= CAP_THRESHOLD) {
		newStatus = BTNLEFT;
	} else if(CircuitPlayground.rightButton()
	|| CircuitPlayground.readCap(9, CAP_SAMPLES) >= CAP_THRESHOLD) {
		newStatus = BTNRIGHT;
	}
	// change color modes
	else if(CircuitPlayground.readCap(3, CAP_SAMPLES) >= CAP_THRESHOLD) {
		newStatus = CAPCOLOR;
	} else if(CircuitPlayground.readCap(2, CAP_SAMPLES) >= CAP_THRESHOLD) {
		newStatus = CAPMODE;
	}
	// brightness buttons are repeat buttons
	// hold them to change continuously
	else if(CircuitPlayground.readCap(12, CAP_SAMPLES) >= CAP_THRESHOLD) {
		newStatus = CAPBRIGHTUP;
	} else if(CircuitPlayground.readCap(6, CAP_SAMPLES) >= CAP_THRESHOLD) {
		newStatus = CAPBRIGHTDOWN;
	}
	//
	if(buttonStatus == BUTTONS_OFF && newStatus != BUTTONS_OFF) {
		// act when the buttons are pressed (or don't)
		switch(newStatus) {
		case BTNLEFT:
			if(colorState) {
				currentBiColor = (currentBiColor+1) % NBICOLORS;
			} else {
				currentColor = (currentColor+1) % NCOLORS;
			}
			break;
		case BTNRIGHT:
			currentPattern = (currentPattern+1) % NPATTERNS;
			break;
		case CAPCOLOR:
			colorState = 1 - colorState;
			break;
		case CAPMODE:
			ordreBicolor = 1 - ordreBicolor;
			break;
		}
		buttonStatus = newStatus;
	} else if(buttonStatus != BUTTONS_OFF && newStatus == buttonStatus) {
		// act when a button is kept down
		switch(buttonStatus) {
		case CAPBRIGHTUP:
			brightness = min(MAXBRIGHT,(brightness+1));
			break;
		case CAPBRIGHTDOWN:
			brightness = max(0,(brightness-1));
			break;
		}
	} else if(buttonStatus != BUTTONS_OFF && newStatus == BUTTONS_OFF) {
		// act when a button is released
		buttonStatus = BUTTONS_OFF;
	}
	// activate the correct state (whether it changed or not)
	if(colorState) {
		doBiLightState();
	} else {
		doLightState();
	}
	delay(10);
}
