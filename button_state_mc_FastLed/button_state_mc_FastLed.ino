// Written by Chitrangad Singh with help from examples available freely on web.

// Sketch for 3 effects that can cycle thru using a button push
// I designed it for a floor lamp with diffused cloth/paper to give a nice fire effect.

#include <JC_Button.h>

#include <FastLED.h>
FASTLED_USING_NAMESPACE

#define DATA_PIN    0
#define COLOR_ORDER GRB
#define NUM_LEDS    30
CRGB leds[NUM_LEDS];
#define BRIGHTNESS          255
#define FRAMES_PER_SECOND 30
bool gReverseDirection = false;
uint8_t bpm = 30;
uint8_t fadeval = 240;  

const int buttonPin = 2;                                      // Digital pin used for debounced pushbutton
Button myBtn(buttonPin, true, true, 50);                      // Declare the button

void setup() {
  //Serial.begin(57600);
  pinMode(buttonPin, INPUT_PULLUP);
  FastLED.addLeds<WS2812,DATA_PIN,COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  FastLED.setBrightness(BRIGHTNESS);
  }

typedef void (*SimplePatternList[])();
SimplePatternList gPatterns = {Fire2012,rainbow,sinelon};
uint8_t gCurrentPatternNumber = 0; // Index number of which pattern is current
uint8_t gHue = 0; // rotating "base color" used by many of the patterns

void loop() {
  random16_add_entropy( random());
  #define COOLING  55
  #define SPARKING 120
  
  gPatterns[gCurrentPatternNumber]();
  // send the 'leds' array out to the actual LED strip
  FastLED.show();  
  // insert a delay to keep the framerate modest
  FastLED.delay(1000/FRAMES_PER_SECOND); 

  // do some periodic updates
  EVERY_N_MILLISECONDS( 20 ) { gHue++; } // slowly cycle the "base color" through the rainbow
//  EVERY_N_SECONDS( 10 ) { nextPattern(); } // change patterns periodically
    readbutton();                               
}

#define ARRAY_SIZE(A) (sizeof(A) / sizeof((A)[0]))
void nextPattern()
{
  // add one to the current pattern number, and wrap around at the end
  gCurrentPatternNumber = (gCurrentPatternNumber + 1) % ARRAY_SIZE( gPatterns);
}


void readbutton() {                                           // Read the button and increase the mode
  myBtn.read();
  if(myBtn.wasPressed()) {
    nextPattern();
  }
} // readbutton()


void Fire2012()
{
// Array of temperature readings at each simulation cell
  static byte heat[NUM_LEDS];

  // Step 1.  Cool down every cell a little
    for( int i = 0; i < NUM_LEDS; i++) {
      heat[i] = qsub8( heat[i],  random8(0, ((COOLING * 10) / NUM_LEDS) + 2));
    }
  
    // Step 2.  Heat from each cell drifts 'up' and diffuses a little
    for( int k= NUM_LEDS - 1; k >= 2; k--) {
      heat[k] = (heat[k - 1] + heat[k - 2] + heat[k - 2] ) / 3;
    }
    
    // Step 3.  Randomly ignite new 'sparks' of heat near the bottom
    if( random8() < SPARKING ) {
      int y = random8(7);
      heat[y] = qadd8( heat[y], random8(160,255) );
    }

    // Step 4.  Map from heat cells to LED colors
    for( int j = 0; j < NUM_LEDS; j++) {
      CRGB color = HeatColor( heat[j]);
      int pixelnumber;
      if( gReverseDirection ) {
        pixelnumber = (NUM_LEDS-1) - j;
      } else {
        pixelnumber = j;
      }
      leds[pixelnumber] = color;
    }
  }


void rainbow() 
{
  // built-in FastLED rainbow, plus some random sparkly glitter
        fill_rainbow(leds, NUM_LEDS, gHue, 5);
        //addGlitter(80);
}

void sinelon()
{
  // colored stripes pulsing at a defined Beats-Per-Minute (BPM)
  uint8_t BeatsPerMinute = 20;
  CRGBPalette16 palette = LavaColors_p;//CloudColors_p; //LavaColors_p; OceanColors_p; ForestColors_p HeatColors_p
  uint8_t beat = beatsin8( BeatsPerMinute, 64, 255);
  for( int i = 0; i < NUM_LEDS; i++) { //9948
    leds[i] = ColorFromPalette(palette, gHue+(i*2), beat-gHue+(i*10));
  }
}

void confetti() 
{
  // random colored speckles that blink in and fade smoothly
  fadeToBlackBy( leds, NUM_LEDS, 10);
  int pos = random16(NUM_LEDS);
  leds[pos] += CHSV( gHue + random8(64), 200, 255);
}
