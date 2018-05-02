
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
long duration = 0;
long distance = 0;

void setup() {
  pinMode(TriggerPin,OUTPUT);  // Trigger is an output pin
  pinMode(EchoPin,INPUT);      // Echo is an input pin
  Serial.begin(9600);          // Serial Output
}

void loop() {
  // In order to generate the ultrasound you need to set the Trig on a High State for 10 µs. 
  // That will send out an 8 cycle sonic burst which will travel at the speed sound and 
  // it will be received in the Echo pin. The Echo pin will output the time in microseconds 
  // the sound wave traveled.
  
  digitalWrite(TriggerPin, LOW);                   
  delayMicroseconds(2);
  digitalWrite(TriggerPin, HIGH);          // Trigger pin to HIGH
  delayMicroseconds(10);                   // 10us high 
  digitalWrite(TriggerPin, LOW);           // Trigger pin to LOW
 
  duration = pulseIn(EchoPin,HIGH);        // Waits for the echo pin to get high
                                           // returns the Duration in microseconds
  distance = getDistance(duration);        // Use function to calculate the distance
 
  Serial.print("Distance = ");             // Output to serial
  Serial.print(distance);
  Serial.println(" mm");
 
  delay(1000);                             // Wait to do next measurement
}

long getDistance(long time) {
    // Calculates the Distance in cm
    // ((time in microseconds)*(Speed of sound)) / toward and backward of object)
    
    // Calculates the Distance in mm
    // (distance in cm) * 10
   
    long distanceCalc;                      // Calculation variable

    //distanceCalc = (time * 0.034) / 2;      // Actual calculation in cm
    distanceCalc = (time * 0.034 * 10) / 2; // Actual calculation in mm
    //distanceCalc = ((time /2.9) / 2);     // Actual calculation in mm
    //DistanceCalc = time / 74 / 2;         // Actual calculation in inches
    return distanceCalc;                    // return calculated value
}



