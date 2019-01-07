// Written by Chitrangad Singh with help from examples available freely on web.

// code for ATtiny85
// fades LEDs on all five pins on and off using software PWM

#define fadeSpeed 5
#define dim 4

void setup()
{
  for (int t = 0; t < 5; t++)
    pinMode(t, OUTPUT);
  randomSeed(1234);
}

void loop()
{
    int pin = random(0,5);
    delay(100);
    for (int fade = 1; fade < 255; fade++)
    {
      softPWM(pin, fade, fadeSpeed);
    }
    for (int fade = 255; fade > 1; fade--)
    {
      softPWM(pin, fade, dim);
    }
  }
// software PWM function that fakes analog output
void softPWM(int pin, int freq, int sp)
{
  digitalWrite(pin, LOW); //on
  delayMicroseconds(sp * freq);
  digitalWrite(pin, HIGH); //off
  delayMicroseconds(sp * (255 - freq));
}
