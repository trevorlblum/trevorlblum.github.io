/*   Blink - 6/5/2021 works on pico 2040 without any changes

  Turns Builtin LED on for one second, then off for one second, repeatedly.
  Source : http://www.arduino.cc/en/Tutorial/Blink
*/

void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on 
  delay(1000);                       // wait for a second
  digitalWrite(LED_BUILTIN, LOW);    // turn the LED off 
  delay(1000);                       // wait for a second
}
