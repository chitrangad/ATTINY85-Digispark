// Written by Chitrangad Singh with help from examples available freely on web.
// Code to trigger a macro to lock the PC and leave a message once the Digispark is plugged in a USB port on a pc.
// there is also a code to randomly blink a neopixel hooked to the same Digispark. 
// This can be omitted or used as a flashing reminder for your forgetful friend.

#include <Adafruit_NeoPixel.h>
#define PIXEL_COUNT 1
#define PIXEL_PIN 0
byte i =0;
unsigned long start = millis();
//#define duration 2000
Adafruit_NeoPixel strip = Adafruit_NeoPixel(PIXEL_COUNT, PIXEL_PIN, NEO_GRB + NEO_KHZ800);

// start USB Key declaration

#include <avr/pgmspace.h>
#include "DigiKeyboard.h"
const char line1[] PROGMEM = "notepad";
const char line2[] PROGMEM = "You forgot to lock your PC.";

char buffer[256];

#define GetPsz(x) (strncpy_P(buffer, (char*)x, 256))
#define KEY_UP_ARROW    0x52
#define KEY_DOWN_ARROW  0x51
#define KEY_LEFT_ARROW    0x50
#define KEY_RIGHT_ARROW   0x4F
#define KEY_LEFT_GUI      0xE3
#define KEY_ESC       0x29
#define KEY_TAB       0x2B

void digiBegin() {
  DigiKeyboard.sendKeyStroke(0,0);
  DigiKeyboard.delay(50);
}

void digiEnd() {
  const int led=1;
  pinMode(led, OUTPUT);
  while (1) {
    digitalWrite(led, !digitalRead(led));
    DigiKeyboard.delay(1000);
  }
}

void printText(char *txt) {
  DigiKeyboard.print(txt);
  DigiKeyboard.update();
}
// End USB Key declarations

void setup()
{
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'

//USB setup begin

digiBegin();

  // Leave a little reminder to lock your PC (just delete or comment this out if you don't want that)
  DigiKeyboard.sendKeyStroke(KEY_R,MOD_GUI_LEFT);

  DigiKeyboard.delay(300);

  // notepad
  printText(GetPsz(line1));

  DigiKeyboard.delay(300);

  DigiKeyboard.sendKeyStroke(KEY_ENTER);

  DigiKeyboard.delay(300);

  // You forgot to lock your PC.
  printText(GetPsz(line2));

  DigiKeyboard.delay(3000);

  // Lock the PC
  DigiKeyboard.sendKeyStroke(KEY_L,MOD_GUI_LEFT);

  digiEnd();
//USB setup ends
}

void loop() {
  randomSeed(0);
  unsigned long duration = random(500,1000);
  byte fade = 250;
  unsigned long current;
  switch (i) {
    case 0:
      do {
        current = millis();
        setpixel(0, 255, 0, 0, fade); //red
        //delay(fade);
      } while (current-start<duration);
      break;
    case 1:
      do {
        current = millis();
        setpixel(0, 0, 255, 0, fade); //green
        } while (current-start<duration);
      break;
    case 2:
      do {
        current = millis();
        setpixel(0, 0, 0, 255, fade); //blue
      } while (current-start<duration);
      break;
    case 3:
      do {
        current = millis();
        setpixel(0, 255, 0, 200, fade); //pink
      } while (current-start<duration);
      break;
    case 4:
      do {
        current = millis();
        setpixel(0, 255, 255, 255, fade); //white
      } while (current-start<duration);
      break;
    case 5:
      do {
        current = millis();
        setpixel(0, 0, 50, 255, fade);
         } while (current-start<duration);
      break;
      case 6:
      do {
        current = millis();
        setpixel(0, 255, 100, 0, fade); //orange
         } while (current-start<duration);
      break;
      case 7:
      do {
        current = millis();
        setpixel(0, 0, 200, 100, fade); //torquoise
         } while (current-start<duration);
      break;
      case 8:
      do {
        current = millis();
        setpixel(0, 50, 255,0 , fade);
         } while (current-start<duration); //sky blue
      break;
    default:
      setpixel(0, 0, 0, 0, fade); //turn off
      i=-1;
      break;
  }
  i++;
  start=millis();
}

void setpixel(byte pixel, byte red, byte green, byte blue, byte speed)
{
  strip.setPixelColor(pixel, red, green, blue);
  strip.show();
  delay(speed);
  strip.setPixelColor(pixel, 0, 0, 0);
  strip.show();
  delay(speed);
}
