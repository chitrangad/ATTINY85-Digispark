// Sketch to cycle thru 3 patterns on a newopixel strip with a button press.
// Simulates sparkles, colorful fireflies and a rainbow sinelon pattern.

// Written by Chitrangad Singh with help from examples available freely on web.
 
#include <JC_Button.h>
#include <FastLED.h>
 
// define the LEDs
#define LED_PIN 0  //pin the LEDs are connected to
#define NUM_LEDS 30  
#define LED_TYPE    WS2812
#define COLOR_ORDER RGB
 
struct CRGB leds[NUM_LEDS];

#define UPDATES_PER_SECOND 120
 
// define the buttons that we'll use.
const int buttonPin = 1;                                      // Digital pin used for debounced pushbutton
Button myBtn(buttonPin, true, true, 50);  

// some counter to keep state 
int Counter = 0;
int hue =0;

void setup() {
 
  delay(300); // power-up safety delay - DO NOT REMOVE
  FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
  FastLED.setBrightness(255);
}
 
void loop() {

  readbutton();
  ChangePattern();
  FastLED.show();
  FastLED.delay(1000 / UPDATES_PER_SECOND);  
}
 
void readbutton() {                                           // Read the button and increase the mode
     myBtn.read();
     if(myBtn.wasPressed()) {
     Counter++;
     if (Counter > 2) { // adjust if you have more or less palettes
      Counter = 0;
      }
  }
} // readbutton()

 
void ChangePattern()
{    
    if( Counter == 1)  { sinelon();}
    if( Counter == 2)  { TwinkleRandom(); }
    if( Counter == 0)  { firefly();}
    if( Counter == 3)  {
}



void TwinkleRandom() {
  leds[random(0,31)] = CHSV(random(255), random(255),255);
    //FastLED.show();
    FastLED.delay(30);
   fill_solid(leds,NUM_LEDS, CRGB::Black); 
}

void firefly(){
    leds[random(0,30)] = CHSV(random(255), 255, 255);
    FastLED.delay(30);
    leds[random(0,30)] = CHSV(random(255), 255, 0);
    FastLED.delay(30);
    //leds[random(0,31)]=CRGB::Black;
}

void sinelon()
{
   uint8_t BeatsPerMinute = 20;
  CRGBPalette16 palette = RainbowColors_p;//CloudColors_p; //LavaColors_p; OceanColors_p; ForestColors_p HeatColors_p
  uint8_t beat = beatsin8( BeatsPerMinute, 64, 255);
  for( int i = 0; i < NUM_LEDS; i++) { //9948
    leds[i] = ColorFromPalette(palette, hue+(i*2), beat-hue+(i*10));
  }
  EVERY_N_MILLISECONDS(50) {hue++;}
}
