
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

// Golden Ratio
float PHI = 1 - 0.618;


///////////////////////
// Debug / Test vars
///////////////////////

boolean debug = true;
boolean neopixelsTest = false;

/////////////////
// Sensor vars
/////////////////

#define PIN_TRIGGER  8      //Trig pin
#define PIN_ECHO     9      //Echo pin

// Trim values to set minimum and maximum ranges (will be about actual distances in cm's / 29)
// The position of the golden cut will be worked out as relative to these two points
// What is the base line sensor value which you want to count as being 0
int TRIM_MIN = 3; //200;
// What is the maximum sensor value which you want to measure to
int TRIM_MAX = 100; //960;

// Delay between sensor reads
#define SENSOR_READ_INTERVAL  800
unsigned long lastTime = 0;

////////////////////
// NeoPixels vars
////////////////////

#define PIN_I 6
#define PIN_O 7
#define NUM_LEDS_I 32
#define NUM_LEDS_O 60
#define BRIGHTNESS 50
#define MAX_GLITCH_DELAY 200

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS_I, PIN_I, NEO_GRBW + NEO_KHZ800);
Adafruit_NeoPixel ring = Adafruit_NeoPixel(NUM_LEDS_O, PIN_O, NEO_GRBW + NEO_KHZ800);

float currentRate;
float maxGlitchDelay;


///////////
// Setup
///////////

void setup() {

  // Init NeoPixels
  initNeoPixel(&strip);
  initNeoPixel(&ring);

  if (!neopixelsTest) {
    pinMode(PIN_TRIGGER, OUTPUT);  // Trigger is an output pin
    pinMode(PIN_ECHO, INPUT);      // Echo is an input pin
    if (debug) {
      Serial.begin(9600);        // Serial Output
    } 
  }
}


///////////
// Loop
///////////

void loop() {
  
  // Read data from ultrasonic sensor and update NeoPixels
  if (!neopixelsTest) {
    
    // Read from sensor
    if (millis() - lastTime > SENSOR_READ_INTERVAL) {

      Serial.println("READ");

      // Distance and distance coefficient
      int distance = getData();
      float coefficient = normalise(distance);

      // Current rate / glitch delay
      currentRate = getRate(coefficient);
      maxGlitchDelay = currentRate * MAX_GLITCH_DELAY;
      
      if (debug) {
        Serial.print("Distance = ");
        Serial.print(distance);
        Serial.println(" cm");
    
        Serial.print("Coefficient = ");
        Serial.print(coefficient);
        Serial.println(" ");

        Serial.print("Rate = ");
        Serial.print(currentRate);
        Serial.println(" ");

        Serial.print("maxGlitchDelay = ");
        Serial.print(maxGlitchDelay);
        Serial.println(" ");
        Serial.println(" ");
      }

      lastTime = millis();
    }

    // Glitch Phi
    fullWhite(&strip);
    delay(random(0, maxGlitchDelay));
    fullWhite(&ring);
    delay(random(0, maxGlitchDelay));
    fullBlack(&strip);
    delay(random(0, maxGlitchDelay));
    fullBlack(&ring);
    delay(random(0, maxGlitchDelay));


  // NeoPixel test only (no data read)
  } else {
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
  }
}



