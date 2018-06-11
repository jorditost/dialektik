#include <Servo.h> 
  
Servo myServo;
#define PIN_SERVO 9
 
void setup() { 
  myServo.attach(PIN_SERVO);
} 
  
 
void loop() { 
  int d = 10;
  int delayMS = 1500;
  int i = 0;
  
  for ( i = 1; i < 99; i += d ) {
    SetStrokePerc(i);
    delay(delayMS);
  }
  
  for ( i = 99; i > 1;  i -= d ) {
    SetStrokePerc(i);
    delay(delayMS);
  }
}
