#include <JC_Button.h>

// This sketch implements FastLED palettes for different kinds of Fire simulations. There is also a standard rainbow effect.
// The palettes and effect can be changed by pressing the button. It also turns off the strip as the last option so you not have to swithc off the mains.

// Written by Chitrangad Singh with help from examples available freely on web.

#include <FastLED.h>
FASTLED_USING_NAMESPACE

#define DATA_PIN    0
#define COLOR_ORDER GRB
#define NUM_LEDS    30
CRGB leds[NUM_LEDS];
#define FRAMES_PER_SECOND 30
uint8_t bpm = 30;
uint8_t fadeval = 240;  
int paletteCounter = 0;
CRGBPalette16 gPal=HeatColors_p;
const int buttonPin = 2; 
bool gReverseDirection = false;
// Digital pin used for debounced pushbutton
Button myBtn(buttonPin, true, true, 50);                      // Declare the button

void setup() {
  pinMode(buttonPin, INPUT_PULLUP);
  FastLED.addLeds<WS2812,DATA_PIN,COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  FastLED.setBrightness(255);
  }

 uint8_t gHue = 0;

void loop() {
 random16_add_entropy( random());
 Fire2012WithPalette(gPal);
 readbutton();
 switch(paletteCounter) {
   case 0:
    gPal = HeatColors_p;
    break;
   case 1:
    gPal = OceanColors_p;
    break;
   case 2:
    gPal = RainbowStripeColors_p;
    break;
   case 3:
    rainbow();
    gHue++; //  cycle the "base color" through the rainbow  
    break;
   default:
    fill_solid(leds, NUM_LEDS,CRGB::Black);
    paletteCounter=-1;
   }
  FastLED.show();  
  FastLED.delay(1000/FRAMES_PER_SECOND);                          
}


void readbutton() {                                           // Read the button and increase the mode
     myBtn.read();
     if(myBtn.wasPressed()) {
     paletteCounter++;
  }
} // readbutton()


#define COOLING  55
#define SPARKING 120

void Fire2012WithPalette(CRGBPalette16 gPal)
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
      // Scale the heat value from 0-255 down to 0-240
      // for best results with color palettes.
      byte colorindex = scale8( heat[j], 240);
      CRGB color = ColorFromPalette( gPal, colorindex);
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
