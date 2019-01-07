// Written by Chitrangad Singh with help from examples available freely on web.

//  This example shows how to fade 4 LEDs on Digispark (ATTINY85 board) using the analogWrite() function.
// I'm trying to simulate a police car light with random blinks in between.
// Use a combination of Bright white and Blue 5mm LEDs for good effect.

int i = 300;
int led1 = 0;           // the pins the LEDs are attached to
int led2 = 1;
int led3 = 2;
int led4 = 4;
int bright = 0;
int brightness1 = 0;    // how bright the LEDs are
int brightness2 = 255;
int brightness3 = 0;
int brightness4 = 255;
int fadeAmount = 5;       // how many points to fade the LED by

void setup() {
  // declare pin 9 to be an output:
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);
  randomSeed(1);
 }

// the loop routine runs over and over again forever:
void loop() {
  if(i <= 0) 
{
  for(int j=0;j<random(100,300);j++)
  {
  analogWrite(random(0,5), 0);
  delay(20);
  analogWrite(random(0,5), 255);
  delay(20);
  analogWrite(random(0,5), 0);
  delay(20);
  analogWrite(random(0,5), 255);
  delay(20);
  analogWrite(random(0,5), 0);
  delay(20);
  analogWrite(random(0,5), 255);
  delay(20);
  analogWrite(random(0,5), 0);
  delay(20);
  analogWrite(random(0,5), 255);
  }
  i = 300;
  }

  // set the brightness of pin 9:
  analogWrite(led1, brightness1);
  analogWrite(led2, brightness2);
  analogWrite(led3, brightness3);
  analogWrite(led4, brightness4);
  
  bright = bright + fadeAmount;
  // change the brightness for next time through the loop:
  
  brightness1 = brightness1 + fadeAmount;
  
  brightness2 = brightness2 - fadeAmount;
  
  brightness3 = brightness3 + fadeAmount;
  
  brightness4 = brightness4 - fadeAmount;
  
    // reverse the direction of the fading at the ends of the fade:
  if (bright <= 0 || bright >= 255) {
    fadeAmount = -fadeAmount;
  }
 
   // wait for 30 milliseconds to see the dimming effect
  delay(25);
  i = i-random(1,2);
}
