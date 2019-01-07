// this sketch makes use of a button library.
// get the buttons lib from here:
// http://playground.arduino.cc/Code/Buttons
 
#include <JC_Button.h>
#include <FastLED.h>
 
// define the LEDs
#define LED_PIN 0  //pin the LEDs are connected to
#define NUM_LEDS 30  
#define LED_TYPE    WS2812
#define COLOR_ORDER RGB
 
struct CRGB leds[NUM_LEDS];

#define UPDATES_PER_SECOND 100
 
CRGBPalette16 currentPalette;
TBlendType    currentBlending;
 
extern CRGBPalette16 myRedWhiteBluePalette;
extern const TProgmemPalette16 myRedWhiteBluePalette_p PROGMEM;
 
const int buttonPin = 1;                                      // Digital pin used for debounced pushbutton
Button myBtn(buttonPin, true, true, 50);  

//Button paletteButton;
//paletteButton.assign(1);  

// some counters to keep state 
int paletteCounter = 0;

void setup() {
 
  delay(300); // power-up safety delay - DO NOT REMOVE
 
  FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
  FastLED.setBrightness(255);
  FastLED.clear();
}
 
void loop() {

  readbutton();
  ChangePalettePeriodically();
  static uint8_t startIndex = 0;
  startIndex = startIndex + 1;
  FillLEDsFromPaletteColors(startIndex);
  FastLED.show();
  FastLED.delay(1000 / UPDATES_PER_SECOND);  
}
 
void readbutton() {                                           // Read the button and increase the mode
     myBtn.read();
     if(myBtn.wasPressed()) {
     paletteCounter++;
     if (paletteCounter > 3) { // adjust if you have more or less palettes
      paletteCounter = 0;
      }
  }
} // readbutton()

 
extern CRGBPalette16 myRedWhiteBluePalette;
extern const TProgmemPalette16 myRedWhiteBluePalette_p PROGMEM;
 
void fillSolid(uint32_t colour) {      
  fill_solid(leds, NUM_LEDS, colour);
}
 
void FillLEDsFromPaletteColors( uint8_t colorIndex)
{
  uint8_t brightness = 255;
  
  for( int i = 0; i < NUM_LEDS; i++) {
    leds[i] = ColorFromPalette( currentPalette, colorIndex, brightness, currentBlending);
    colorIndex += 3;
  }
}

 
// There are several different palettes of colors demonstrated here.
//
// FastLED provides several 'preset' palettes: RainbowColors_p, RainbowStripeColors_p,
// OceanColors_p, CloudColors_p, LavaColors_p, ForestColors_p, and PartyColors_p.
//
// Additionally, you can manually define your own color palettes, or you can write
// code that creates color palettes on the fly.  All are shown here.
 
void ChangePalettePeriodically()
{    
    if( paletteCounter == 0)  { currentPalette = RainbowStripeColors_p;   currentBlending = LINEARBLEND; }
    //if( paletteCounter == 2)  { currentPalette = OceanColors_p;           currentBlending = NOBLEND;  }
    if( paletteCounter == 1)  { TwinkleRandom(); }
    //if( paletteCounter == 3)  { currentPalette = LavaColors_p;            currentBlending = LINEARBLEND;  }
    if( paletteCounter == 2)  { currentPalette = PartyColors_p;           currentBlending = LINEARBLEND;  }
    //if( paletteCounter == 3)  { SetupTotallyRandomPalette();              currentBlending = LINEARBLEND; }
    if( paletteCounter == 3)  { currentPalette = myRedWhiteBluePalette_p; currentBlending = NOBLEND;  }
}



void TwinkleRandom() {
 int i = random8(NUM_LEDS);
  if (i < NUM_LEDS) leds[i] = CHSV(random(255), 255, 255);
  for (int j = 0; j < NUM_LEDS; j++) leds[j].fadeToBlackBy(8); // Smaller value = LEDs change colour in fading out : (
  FastLED.show();
  FastLED.delay(50);
}
// This function fills the palette with totally random colors.
void SetupTotallyRandomPalette()
{
  for( int i = 0; i < 16; i++) {
    currentPalette[i] = CHSV( random8(), 255, random8());
  }
}
 
// This function sets up a palette of black and white stripes,
// using code.  Since the palette is effectively an array of
// sixteen CRGB colors, the various fill_* functions can be used
// to set them up.
void SetupBlackAndWhiteStripedPalette()
{
  // 'black out' all 16 palette entries...
  fill_solid( currentPalette, 16, CRGB::Black);
  // and set every fourth one to white.
  currentPalette[0] = CRGB::White;
  currentPalette[4] = CRGB::White;
  currentPalette[8] = CRGB::White;
  currentPalette[12] = CRGB::White;
 
}
 
// This function sets up a palette of purple and green stripes.
void SetupPurpleAndGreenPalette()
{
  CRGB purple = CHSV( HUE_PURPLE, 255, 255);
  CRGB green  = CHSV( HUE_GREEN, 255, 255);
  CRGB black  = CRGB::Black;
 
  currentPalette = CRGBPalette16(
    green,  green,  black,  black,
    purple, purple, black,  black,
    green,  green,  black,  black,
    purple, purple, black,  black );
}
 
 
// This example shows how to set up a static color palette
// which is stored in PROGMEM (flash), which is almost always more
// plentiful than RAM.  A static PROGMEM palette like this
// takes up 64 bytes of flash.
const TProgmemPalette16 myRedWhiteBluePalette_p PROGMEM =
{
  CRGB::Red,
  CRGB::Gray, // 'white' is too bright compared to red and blue
  CRGB::Blue,
  CRGB::Black,
 
  CRGB::Red,
  CRGB::Gray,
  CRGB::Blue,
  CRGB::Black,
 
  CRGB::Red,
  CRGB::Red,
  CRGB::Gray,
  CRGB::Gray,
  CRGB::Blue,
  CRGB::Blue,
  CRGB::Black,
  CRGB::Black
};
 
