// Simple sketch to cycle thru all rainbow colors for a single neopixel. Can be used as an electronic badge or a lone star at the top of x-mas tree

// Written by Chitrangad Singh with help from examples available freely on web.

#include <FastLED.h>

FASTLED_USING_NAMESPACE

#define DATA_PIN    0
#define LED_TYPE    WS2812
#define COLOR_ORDER GRB
#define NUM_LEDS    1
CRGB leds[NUM_LEDS];

#define strobe 30

void setup() {
  FastLED.addLeds<LED_TYPE,DATA_PIN,COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  //FastLED.setBrightness(10);
}

uint8_t hue = 0; // rotating "base color" used by many of the patterns
unsigned long start = millis();
int duration = 0;

  
void loop()
{
   for(int i=0;i<255;i++){
    for(int j=0;j<10;j++){
        leds[0]=CHSV(i,255,255);
        FastLED.show();
        delay(100);
        leds[0]=CRGB::Black;
        FastLED.show();
        delay(100);
     }
     i=i+20;
   }
}
