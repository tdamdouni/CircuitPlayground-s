//NeoAnim for Circuit Playground
// adapted by John Park from Circuit Playground Make Believe by Phil Burgess
// for Adafruit Industries
// MIT License

#include <Adafruit_CircuitPlayground.h>
#include "neoAnim.h" //this is the name of the animation derrived from the neoAnim.png bitmap file


void setup() {
  // Initialize Circuit Playground board, NeoPixels
  CircuitPlayground.begin();
  CircuitPlayground.strip.setBrightness(20); 

  // Start looping animation
  playAnim( neoAnimPixelData, neoAnimFPS       , sizeof(neoAnimPixelData), true);
}

// Global values used by the animation and sound functions
uint16_t         *pixelBaseAddr, // Address of active animation table
                  pixelLen,      // Number of pixels in active table
                  pixelIdx,      // Index of first pixel of current frame
                  audioLen;      // Number of audio samples in active table
volatile uint16_t audioIdx;      // Index of current audio sample
uint8_t           pixelFPS,      // Frames/second for active animation
                 *audioBaseAddr; // Address of active sound table
boolean           pixelLoop,     // If true, animation repeats
                  audioLoop;     // If true, audio repeats
  
// Begin playing a NeoPixel animation from a PROGMEM table
void playAnim(const uint16_t *addr, uint8_t fps, uint16_t bytes, boolean repeat) {
  pixelBaseAddr = addr;
  if(addr) {
    pixelFPS    = fps;
    pixelLen    = bytes / 2;
    pixelLoop   = repeat; //if set to 'repeat' it'll loop, set to 0 to play once only
    pixelIdx    = 0;
  } else {
    CircuitPlayground.strip.clear();
  }
}

uint32_t prev = 0; // Time of last NeoPixel refresh

void loop() {
  uint32_t t;      // Current time in milliseconds
  
  // Until the next animation frame interval has elapsed...
  while(((t = millis()) - prev) < (1000 / pixelFPS));
    // Show LEDs rendered on prior pass.  It's done this way so animation timing
    // is a bit more consistent (frame rendering time may vary slightly).
    CircuitPlayground.strip.show();
  
   
  prev = t; // Save refresh time for next frame sync

  if(pixelBaseAddr) {
    for(uint8_t i=0; i<10; i++) { // For each NeoPixel...
      // Read pixel color from PROGMEM table
      uint16_t rgb = pgm_read_word(&pixelBaseAddr[pixelIdx++]);
      // Expand 16-bit color to 24 bits using gamma tables
      // RRRRRGGGGGGBBBBB -> RRRRRRRR GGGGGGGG BBBBBBBB
      CircuitPlayground.strip.setPixelColor(i,
        pgm_read_byte(&gamma5[ rgb >> 11        ]),
        pgm_read_byte(&gamma6[(rgb >>  5) & 0x3F]),
        pgm_read_byte(&gamma5[ rgb        & 0x1F]));
    }
  
     
      if(pixelIdx >= pixelLen) { // End of animation table reached
        if(pixelLoop) { // Repeat animation
          pixelIdx = 0; // Reset index to start of table
        } else {        // else switch off LEDs
          playAnim(NULL, neoAnimFPS, 0, false);
        }
      } 
  
  }
}

