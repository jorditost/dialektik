/*
  Melody

  Plays a melody

  circuit:
  - 8 ohm speaker on digital pin 10

  created 21 Jan 2010
  modified 30 Aug 2011
  by Tom Igoe

  This example code is in the public domain.

  http://www.arduino.cc/en/Tutorial/Tone
*/

#define PIN_PIEZO 10

void setup() {
  
}

void loop() {
  int freq = random(200, 5000);
  tone(PIN_PIEZO, freq);
  delayMicroseconds(20); //random(1,20)
  noTone(PIN_PIEZO);
  delayMicroseconds(10); //random(1,10)
}
