
/*
dialektik
=============

input: HC-SR04 Ultrasonic Sensor
output: Some Adafruit NeoPixels in PHI form
*/

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

const int TriggerPin = 8;      //Trig pin
const int EchoPin = 9;         //Echo pin

boolean debug = true;
boolean neopixels_test = true;

// Trim values to set minimum and maximum ranges (will be about actual distances in cm's / 29)
// The position of the golden cut will be worked out as relative to these two points
// What is the base line sensor value which you want to count as being 0
int TRIM_MIN = 10; //200;
// What is the maximum sensor value which you want to measure to
int TRIM_MAX = 300; //960;

// Golden Ratio
float PHI = 1 - 0.618;

// NeoPixels
#define PIN_I 6
#define PIN_O 7
#define NUM_LEDS_I 32
#define NUM_LEDS_O 60
#define BRIGHTNESS 50

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS_I, PIN_I, NEO_GRBW + NEO_KHZ800);
Adafruit_NeoPixel ring = Adafruit_NeoPixel(NUM_LEDS_O, PIN_O, NEO_GRBW + NEO_KHZ800);

void setup() {
  pinMode(TriggerPin,OUTPUT);  // Trigger is an output pin
  pinMode(EchoPin,INPUT);      // Echo is an input pin
  if (debug) {
    Serial.begin(9600);        // Serial Output
  }

  initNeoPixel(&strip);
  initNeoPixel(&ring);
}

void loop() {

  // NeoPixel test only (no data read)
  if (neopixels_test) {
    
    colorWipe(&strip, Adafruit_NeoPixel::Color(255, 0, 0), 50); // Red
    colorWipe(&ring, Adafruit_NeoPixel::Color(0, 255, 0), 50); // Green
    colorWipe(&strip, Adafruit_NeoPixel::Color(0, 0, 255), 50); // Blue
    colorWipe(&ring, Adafruit_NeoPixel::Color(0, 0, 0, 255), 50); // White
    
    pulseWhite(&strip, 0);
    //pulseWhite(&ring, 0);
  
    whiteOverRainbow(&ring,20,75,5);  
  
    pulseWhite(&strip, 5); 
  
    // fullWhite();
    // delay(2000);
  
    rainbowFade2White(&ring,3,3,1);
    
  // Read data from ultrasonic sensor and update NeoPixels
  } else {
    int distance = getData();
    float coefficient = normalise(distance);
    //currentRate = getRate(coefficient);
  
    uint8_t w_value = map(distance, 0, 300, 255, 0);
    
    if (debug) {
      Serial.print("Distance = ");
      Serial.print(distance);
      Serial.println(" cm");
  
      Serial.print("Coefficient = ");
      Serial.print(coefficient);
      Serial.println(" ");
  
      Serial.print("White value = ");
      Serial.print(w_value);
      Serial.println(" ");
      Serial.println(" ");
    }
    
    //colorWipe(strip.Color(0, 0, 0, w_value), 0); // White RGBW
    delay(1000); // Wait to do next measurement
  }
}



