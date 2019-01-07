// Sketch for a singel neopixel mounted on digispark with a button
// Can be used as a digital badge or decorative piece. Can change parretns using a button press.
// Written by Chitrangad Singh with help from examples available freely on web.

#include <FastLED.h>
#include <JC_Button.h>
#include <avr/sleep.h>

FASTLED_USING_NAMESPACE

#define DATA_PIN    0
#define LED_TYPE    WS2812
#define COLOR_ORDER GRB
#define NUM_LEDS    1
CRGB leds[NUM_LEDS];

// Utility macros
#define adc_disable() (ADCSRA &= ~(1<<ADEN)) // disable ADC (before power-off)
#define adc_enable()  (ADCSRA |=  (1<<ADEN)) // re-enable ADC


#define freq 20
const int buttonPin = 4;                                      // Digital pin used for debounced pushbutton
Button myBtn(buttonPin, true, true, 50);  
int pattern=0;

void setup() {
  FastLED.addLeds<LED_TYPE,DATA_PIN,COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  FastLED.setBrightness(250);
  pinMode(buttonPin, INPUT_PULLUP);
  adc_disable(); 
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);
}

uint8_t hue = 0; // rotating "base color" used by many of the patterns
int duration = 0;
  
void loop()
{

  readbutton();
  switch(pattern) {
    case 0:
    sinelon();
    break;
    case 1:
    sunrise();
    break;
    case 2:
    rainbow();
    break;
    case 3:
    leds[0]= CRGB::Green;
    break;
    case 4:
    leds[0]= CRGB::Purple;
    break;
    case 5:
    leds[0]= CRGB::Orange;
    break;
    case 6:
    leds[0]= CRGB::White;
    break;
    default:
    leds[0]=CRGB::Black;
    FastLED.show();
    enterSleep();
  }
  FastLED.show();
  EVERY_N_MILLISECONDS(50) {hue++;}
  }

void readbutton() {                                           // Read the button and increase the mode
     myBtn.read();
     if(myBtn.wasPressed()) {
     pattern++;
     if (pattern > 6)// adjust if you have more or less palettes
      pattern = 0;
  }
} // readbutton()

void sinelon(){
  uint8_t BeatsPerMinute = 40;
  CRGBPalette16 palette = PartyColors_p;
  uint8_t beat = beatsin16( BeatsPerMinute, 64, 255);
  leds[0] = ColorFromPalette(palette, hue, beat-hue);
  FastLED.show();
}

void strobe() {
  leds[0]= CRGB::White;
  FastLED.show();
  FastLED.delay(1000 / freq);
  leds[0]= CRGB::Black;
  FastLED.show();
  FastLED.delay(1000 / freq);
}

void rainbow(){
  fill_rainbow(leds,NUM_LEDS,hue);
  FastLED.show();
}

void sunrise() {
  static const uint8_t interval = 180 / 256;
  CRGB color = ColorFromPalette(HeatColors_p, hue);
  fill_solid(leds, NUM_LEDS, color);
  }

void enterSleep()
{
  sleep_enable();
  //sleep_cpu();
}
