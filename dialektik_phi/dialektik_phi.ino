
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

///////////////////////
// Debug / Test vars
///////////////////////

boolean noiseOn = true;
boolean debug = false;
boolean neopixelsTest = false;


////////////
// Config
////////////

// Trim values to set minimum and maximum ranges (will be about actual distances in cm's / 29) schreib was
// The position of the golden cut will be worked out as relative to these two points

#define DISTANCE_MIN          3    // Enfernung in Centimeter // 200 // What is the base line sensor value which you want to count as being 0
#define DISTANCE_MAX          100  // Enfernung in Centimeter // 960 // What is the maximum sensor value which you want to measure to

#define BLINK_DELAY_MAX       800       // Max time between on/off status while blinking
#define GLITCH                false      // When glitch is true, then the blinking gets more random

#define SENSOR_READ_INTERVAL  50       // Delay between sensor reads

// Golden Ratio
float PHI = 1 - 0.618;
#define MIN_BLINK_RATE        0.0
#define PHI_BUFFER            0.05


/////////////////
// Sensor vars
/////////////////

#define PIN_TRIGGER  8      //Trig pin
#define PIN_ECHO     9      //Echo pin


////////////////////
// NeoPixels vars
////////////////////

#define PIN_I 6
#define PIN_O 7
#define NUM_LEDS_I 40
#define NUM_LEDS_O 60
#define BRIGHTNESS 10

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS_I, PIN_I, NEO_GRBW + NEO_KHZ800);
Adafruit_NeoPixel ring = Adafruit_NeoPixel(NUM_LEDS_O, PIN_O, NEO_GRBW + NEO_KHZ800);

float currentRate;
float maxBlinkDelay;
unsigned long lastTime = 0;


////////////
// Piezo
////////////

#define PIN_PIEZO 10

///////////
// Setup
///////////

void setup() {

  // Init NeoPixels
  initNeoPixel(&strip);
  initNeoPixel(&ring);

  if (noiseOn) {
    setupPiezo();
  }
  
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
    
    // Read from sensor (wie oft wird es gemessen?)
    if (millis() - lastTime > SENSOR_READ_INTERVAL) {

      Serial.println("READ");

      // Distance and distance coefficient
      int distance = getDistance(); // getDistance() kalkuliert die Enfernung zwischen Sensor und Person
      float coefficient = normalise(distance); // coefficient wandelt dieseEntfernung (distance) in einem Wert zwischen 0 und 1

      // Current rate / glitch delay
      currentRate = getRate(coefficient); // getRate() kalkuliert wie schnell 0 und 1 blinken

      maxBlinkDelay = currentRate * BLINK_DELAY_MAX;
      //maxBlinkDelay += 0.1;
      
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

        Serial.print("maxBlinkDelay = ");
        Serial.print(maxBlinkDelay);
        Serial.println(" ");
        Serial.println(" ");
      }

      lastTime = millis();
    }

    // Blink PHI
    if (maxBlinkDelay > 0.01) {

      // strip = 1
      // ring = 0
      
      // Turn I on
      fullWhite(&strip);
      if (noiseOn) makeNoise();
      blinkDelay(maxBlinkDelay, GLITCH);

      // Turn I off
      fullBlack(&strip);
      if (noiseOn) stopNoise();

      // Turn O on
      fullWhite(&ring);
      if (noiseOn) makeNoise();
      blinkDelay(maxBlinkDelay, GLITCH);
      
      // Turn 0 off
      fullBlack(&ring);
      if (noiseOn) stopNoise();
      
    // Show PHI
    } else {
      fullWhite(&strip);
      fullWhite(&ring);
      if (noiseOn) makeNoise();
    }


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

void blinkDelay(float delayTime, boolean isRandomTime) {
  if (isRandomTime) {
    delay(random(0, delayTime)); 
  } else {
    delay(delayTime);
  }
}
