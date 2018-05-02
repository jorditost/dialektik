
/*
HC-SR04 for Arduino

Original project from http://www.swanrobotics.com

This project demonstrates the HC-SR
The distance presented in the code is in mm, but you can uncomment the line for distance in inches.
The schematics for this project can be found on http://www.swanrobotics.com

This example code is in the public domain.
*/

const int TriggerPin = 8;      //Trig pin
const int EchoPin = 9;         //Echo pin

boolean debug = true;

// Trim values to set minimum and maximum ranges (will be about actual distances in cm's / 29)
// The position of the golden cut will be worked out as relative to these two points
// What is the base line sensor value which you want to count as being 0
int TRIM_MIN = 50; //200;
// What is the maximum sensor value which you want to measure to
int TRIM_MAX = 500; //960;

// Golden Ratio
float PHI = 1 - 0.618;


void setup() {
  pinMode(TriggerPin,OUTPUT);  // Trigger is an output pin
  pinMode(EchoPin,INPUT);      // Echo is an input pin
  if (debug) {
    Serial.begin(9600);        // Serial Output
  }
}

void loop() {

  int distance = getData();
  float coefficient = normalise(distance);
  //currentRate = getRate(coefficient);
  
  if (debug) {
    Serial.print("Distance = ");
    Serial.print(distance);
    Serial.println(" cm");

    Serial.print("Coefficient = ");
    Serial.print(coefficient);
    Serial.println(" ");
    Serial.println(" ");
  }
 
  delay(1000); // Wait to do next measurement
}



