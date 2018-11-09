/*
  Noise functions
*/

unsigned long int reg;

void setupPiezo() {
  
  // Connect a piezo sounder between Ground and this pin
  pinMode (PIN_PIEZO, OUTPUT);
  
  // Arbitrary inital value; must not be zero
  reg = 0x55aa55aaL;
}

void makeNoise() {
  unsigned long int newr;
  unsigned char lobit;
  unsigned char b31, b29, b25, b24;
  
  // Extract four chosen bits from the 32-bit register
  b31 = (reg & (1L << 31)) >> 31;
  b29 = (reg & (1L << 29)) >> 29;
  b25 = (reg & (1L << 25)) >> 25;
  b24 = (reg & (1L << 24)) >> 24;
  
  // EXOR the four bits together
  lobit = b31 ^ b29 ^ b25 ^ b24;
  
  // Shift and incorporate new bit at bit position 0
  newr = (reg << 1) | lobit;
  
  // Replace register with new value
  reg = newr;
  
  // Drive speaker pin from bit 0 of 'reg'
  digitalWrite (PIN_PIEZO, reg & 1);
  
  // Display 'reg' in the serial console for debugging only 
//  Serial.println (reg, HEX);
  
  // Delay corresponds to 1/T(m/s), but the actual frequency of updates
  // will be lower, due to computation time and loop overhead
  //delayMicroseconds (50);
}

void stopNoise() {
  digitalWrite(PIN_PIEZO, 0);
}

/*void makeNoise() {

  tone(PIN_PIEZO, 110, 50);
  //delay(100);
  //noTone(PIN_PIEZO);
}

void makeNoiseConstant() {
  tone(PIN_PIEZO, 440);
}

void stopNoise() {
  noTone(PIN_PIEZO);
}*/


