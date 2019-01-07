
// Written by Chitrangad Singh with help from examples available freely on web.
// Simple sketch to fade in-out a single neopixel. Of course there are easier and more eficient ways using FastLED library.
// This is just a demo for one of the ways.

#include <Adafruit_NeoPixel.h>
#define PIXEL_COUNT 1
#define PIXEL_PIN 0
 //unsigned long colors[13] ={0xFF0000,0x00ff00,0x0000ff,0xEDFA39,0xFAB01B,0xFA55DE,0xFA2649,0x62FAE6,0x7FFA53,0xFA0DBB,0xFA7D8E,0x0ABAFA,0xffffff};

Adafruit_NeoPixel strip = Adafruit_NeoPixel(PIXEL_COUNT, PIXEL_PIN, NEO_GRB + NEO_KHZ800);

void setup()
{
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
 
}

void loop() { 
  int fade = random(5,10);
  byte i = random(0,255);
  byte j = random(0,255);
  byte k = random(0,255);
  FadeInOut(i,j,k,fade);
  delay(random(100,1000));
 }

void FadeInOut(byte red, byte green, byte blue, int fade){
  float r, g, b;
      
  for(int k = 0; k < 256; k=k+1) { 
    r = (k/256.0)*red;
    g = (k/256.0)*green;
    b = (k/256.0)*blue;
    setAll(r,g,b);
    strip.show();
   }
     
  for(int k = 255; k >= 0; k=k-2) {
    r = (k/256.0)*red;
    g = (k/256.0)*green;
    b = (k/256.0)*blue;
    setAll(r,g,b);
    strip.show();
    delay(fade);
  }
}


void setAll(byte red, byte green, byte blue) {
  for(int i = 0; i < PIXEL_COUNT; i++ ) {
    strip.setPixelColor(i, strip.Color(red, green, blue)); 
  }
  strip.show();
}
