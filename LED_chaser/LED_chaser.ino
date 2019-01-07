// Written by Chitrangad Singh with help from examples available freely on web.

// A very basic KITT-like LED chanser with 4 LEDs on a Digispark board.
// I used SMD multi-colored LEDs to miniaturize it and sew it on a jacket. Run it off a 3v coin cell.

int i = 10;

void setup() // setup all pins as OUTPUTS to drive current for 
{            // the LEDs.
  pinMode(0, OUTPUT);
  pinMode(1, OUTPUT);
  pinMode(2, OUTPUT);
  pinMode(4, OUTPUT);
 }

void loop(){
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
  i = 10;
  }
  digitalWrite(0, HIGH); // LED0 ON
  delay(100);            // wait 100 ms
  digitalWrite(1, HIGH); // LED1 ON  
  delay(100);            // wait 100 ms
  digitalWrite(2, HIGH); // LED2 ON  
  delay(100);            // wait 100 ms
  digitalWrite(4, HIGH); // LED4 ON  
  delay(100);            // wait 100 ms
  digitalWrite(0, LOW);  // turn off ALL LEDs
  delay(100); 
  digitalWrite(1, LOW);
  delay(100);   
  digitalWrite(2, LOW); 
  delay(100);  
  digitalWrite(4, LOW); 
  delay(100); 
  digitalWrite(4, HIGH); // LED0 ON
  delay(100);            // wait 100 ms
  digitalWrite(2, HIGH); // LED1 ON  
  delay(100);            // wait 100 ms
  digitalWrite(1, HIGH); // LED2 ON  
  delay(100);            // wait 100 ms
  digitalWrite(0, HIGH); // LED4 ON 
  delay(100); 
  digitalWrite(0, LOW);  // turn off ALL LEDs
  delay(100); 
  digitalWrite(1, LOW); 
  delay(100);  
  digitalWrite(2, LOW); 
  delay(100);  
  digitalWrite(4, LOW);
  delay(100);   
  i = i-1;   // 500 ms delay
}
