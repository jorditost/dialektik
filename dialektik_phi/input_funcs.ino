/*
  Input Functions
  Reads from HC-SR04 Ultrasonic Sensor
*/

int getData() {
  // In order to generate the ultrasound you need to set the Trig on a High State for 10 µs. 
  // That will send out an 8 cycle sonic burst which will travel at the speed sound and 
  // it will be received in the Echo pin. The Echo pin will output the time in microseconds 
  // the sound wave traveled.
  
  digitalWrite(PIN_TRIGGER, LOW);                   
  delayMicroseconds(2);
  digitalWrite(PIN_TRIGGER, HIGH);          // Trigger pin to HIGH
  delayMicroseconds(10);                   // 10us high 
  digitalWrite(PIN_TRIGGER, LOW);           // Trigger pin to LOW

  // The sensor returns the duration in microseconds
  long duration = pulseIn(PIN_ECHO,HIGH);   // Waits for the echo pin to get high
  return getDistance(duration);            // Use function to calculate the distance
}

/*
  Get distance from the object in cm. Input is time in microseconds
  ((time in microseconds)*(Speed of sound)) / toward and backward of object)
*/
int getDistance (long time) {
  int distanceCalc;                        // Calculation variable
  distanceCalc = (time / 29) / 2;           // Actual calculation in cm
  //distanceCalc = (time * 0.034) / 2;      // Actual calculation in cm
  return distanceCalc;                      // return calculated value
}


float normalise(int inData) {
  
  if (inData < DISTANCE_MIN) {
    /*if (debug) {
      Serial.print("normalise(): low value ");
      Serial.print(inData);
      Serial.print(" rebased to minimum ");
      Serial.println(DISTANCE_MIN);
    }*/ 
    inData = DISTANCE_MIN;
  }
  
  if (inData > DISTANCE_MAX) {
    /*if (debug) {
      Serial.print("normalise(): high value ");
      Serial.print(inData);
      Serial.print(" rebased to maximum ");
      Serial.println(DISTANCE_MAX);
    }*/ 
    inData = DISTANCE_MAX;
  }
  
  float rebased = inData - DISTANCE_MIN;
  float diff = DISTANCE_MAX - DISTANCE_MIN;
  float normalised = rebased / diff;
  
  /*if (debug) {
    Serial.print("normalise(): input value ");
    Serial.print(inData);
    Serial.print(" rebased to ");
    Serial.println(normalised);
  }*/ 
  
  return normalised;
}

float getRate(float coefficient) {
  
  float rate;
  float ALPHA = PHI + PHI_BUFFER;
  float BETA  = PHI - PHI_BUFFER;

  if (coefficient > ALPHA) {
    rate = MIN_BLINK_RATE + (coefficient - ALPHA) / (1 - ALPHA);
  } else if (coefficient < BETA) {
    rate = MIN_BLINK_RATE + 1 - (coefficient / BETA);
  } else {
    rate = MIN_BLINK_RATE;
  }
  
  /*if (coefficient > PHI-0.1 && coefficient < PHI+0.1) {
    rate = 0.01;//0;
  } else if (coefficient < PHI) {
    rate = 1 - (coefficient / PHI);
  } else {
    rate = (coefficient - PHI) / (1 - PHI);
  }

  // Set a minimum rate
  if (rate < 0.015) {
    rate = 0.01;
  }*/
  
  /*if (coefficient < PHI) {
    rate = 1 + ((coefficient / PHI ) * ( DISPLAY_RATE - 1 ));
  } else {
    float relPos = (coefficient - PHI) / (1 - PHI);
    rate =  1 + ((1 - relPos) * (DISPLAY_RATE - 1));
  }*/
  
  if (debug) {
    Serial.print("getRate(): coefficent value: ");
    Serial.print(coefficient);
    Serial.print(" means rate of : ");
    Serial.println(rate);
  }
  
  return rate;
}
