// Written by Chitrangad Singh with help from examples available freely on web.

// Macro keys using Digispark and Shift Register CD4021. You can customize your routines.

#include "DigiKeyboard.h"

int dataPin = 0;   // Pin 0 of DigiSpark connected to Pin 3 of CD4021
int clockPin = 1;  // Pin 1 of DigiSpark connected to Pin 10 of CD4021
int latchPin = 2;  // Pin 2 of DigiSpark connected to Pin 9 of CD4021
 

byte RegisterValue = 0; 

void setup() {

//define pins used to connect to the CD4021 Shift Register
  pinMode(dataPin, INPUT);
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT); 

}

void loop() {

  //Set latch pin to 1 to get recent data into the CD4021
  digitalWrite(latchPin,1);
  
  delayMicroseconds(20);
  
  //Set latch pin to 0 to get data from the CD4021
  digitalWrite(latchPin,0);

  //Get CD4021 register data in byte variable
  RegisterValue = shiftIn(dataPin, clockPin, MSBFIRST);


  if (RegisterValue == B1000000) {
  DigiKeyboard.sendKeyStroke(KEY_C, MOD_CONTROL_LEFT ); //COPY SHORTCUT (ctrl+c)

  }

  if (RegisterValue == B1000) {
  DigiKeyboard.sendKeyStroke(KEY_V, MOD_CONTROL_LEFT ); //PASTE SHORTCUT (ctrl+v)

  }

  if (RegisterValue == B100) {
  DigiKeyboard.sendKeyStroke(KEY_X, MOD_CONTROL_LEFT ); //CUT key SHORTCUT (ctrl+X)
 
  }

  if (RegisterValue == B10) {
  DigiKeyboard.sendKeyStroke(KEY_F4,MOD_ALT_LEFT ); // Close shortcut key(alt+ F4)
  DigiKeyboard.delay(250);
  }

  if (RegisterValue == B10000) {
  DigiKeyboard.sendKeyStroke(KEY_D,MOD_GUI_LEFT); //  (WINDOWS+D)
  DigiKeyboard.delay(250);
  
  }
  
  if (RegisterValue == B10000000) {
    DigiKeyboard.print("Hello"); // TO PRINT SOMETHING WITH A KEY PRESS
    DigiKeyboard.delay(250);
   
  }

delay(250);

}



