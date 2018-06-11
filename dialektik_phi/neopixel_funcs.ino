/*
  NeoPixels Functions
*/

void initNeoPixel(Adafruit_NeoPixel * np) {
  np->setBrightness(BRIGHTNESS);
  np->begin();
  np->show(); // Initialize all pixels to 'off'
}

// Fill the dots one after the other with a color
void colorWipe(Adafruit_NeoPixel * np, uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<np->numPixels(); i++) {
    np->setPixelColor(i, c);
    np->show();
    delay(wait);
  }
}

void pulseWhite(Adafruit_NeoPixel * np, uint8_t wait) {
  for(int j = 0; j < 256 ; j++){
      for(uint16_t i=0; i<np->numPixels(); i++) {
          np->setPixelColor(i, np->Color(0,0,0, j ) );
        }
        delay(wait);
        np->show();
      }

  for(int j = 255; j >= 0 ; j--){
      for(uint16_t i=0; i<np->numPixels(); i++) {
          np->setPixelColor(i, np->Color(0,0,0, j ) );
        }
        delay(wait);
        np->show();
      }
}

void rainbowFade2White(Adafruit_NeoPixel * np, uint8_t wait, int rainbowLoops, int whiteLoops) {
  float fadeMax = 100.0;
  int fadeVal = 0;
  uint32_t wheelVal;
  int redVal, greenVal, blueVal;

  for(int k = 0 ; k < rainbowLoops ; k ++){
    
    for(int j=0; j<256; j++) { // 5 cycles of all colors on wheel

      for(int i=0; i< np->numPixels(); i++) {

        wheelVal = Wheel(np, ((i * 256 / np->numPixels()) + j) & 255);

        redVal = red(wheelVal) * float(fadeVal/fadeMax);
        greenVal = green(wheelVal) * float(fadeVal/fadeMax);
        blueVal = blue(wheelVal) * float(fadeVal/fadeMax);

        np->setPixelColor( i, np->Color( redVal, greenVal, blueVal ) );
      }

      //First loop, fade in!
      if(k == 0 && fadeVal < fadeMax-1) {
          fadeVal++;
      }

      //Last loop, fade out!
      else if(k == rainbowLoops - 1 && j > 255 - fadeMax ){
          fadeVal--;
      }
        np->show();
        delay(wait);
    }
  }



  delay(500);


  for(int k = 0 ; k < whiteLoops ; k ++){

    for(int j = 0; j < 256 ; j++){
        for(uint16_t i=0; i < np->numPixels(); i++) {
            np->setPixelColor(i, np->Color(0,0,0,j));
        }
        np->show();
    }

    delay(2000);
    for(int j = 255; j >= 0 ; j--){

        for(uint16_t i=0; i < np->numPixels(); i++) {
          np->setPixelColor(i, np->Color(0,0,0,j));
        }
        np->show();
    }
  }

  delay(500);


}

void whiteOverRainbow(Adafruit_NeoPixel * np, uint8_t wait, uint8_t whiteSpeed, uint8_t whiteLength ) {
  
  if(whiteLength >= np->numPixels()) whiteLength = np->numPixels() - 1;

  int head = whiteLength - 1;
  int tail = 0;

  int loops = 3;
  int loopNum = 0;

  static unsigned long lastTime = 0;


  while(true){
    for(int j=0; j<256; j++) {
      for(uint16_t i=0; i<np->numPixels(); i++) {
        if((i >= tail && i <= head) || (tail > head && i >= tail) || (tail > head && i <= head) ){
          np->setPixelColor(i, np->Color(0,0,0, 255 ) );
        }
        else{
          np->setPixelColor(i, Wheel(np, ((i * 256 / np->numPixels()) + j) & 255));
        }
        
      }

      if(millis() - lastTime > whiteSpeed) {
        head++;
        tail++;
        if(head == np->numPixels()){
          loopNum++;
        }
        lastTime = millis();
      }

      if(loopNum == loops) return;
    
      head%=np->numPixels();
      tail%=np->numPixels();
        np->show();
        delay(wait);
    }
  }
  
}
void fullWhite(Adafruit_NeoPixel * np) {
    for(uint16_t i=0; i<np->numPixels(); i++) {
        np->setPixelColor(i, np->Color(0,0,0, 255 ) );
    }
    np->show();
}


// Slightly different, this makes the rainbow equally distributed throughout
void rainbowCycle(Adafruit_NeoPixel * np, uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256 * 5; j++) { // 5 cycles of all colors on wheel
    for(i=0; i< np->numPixels(); i++) {
      np->setPixelColor(i, Wheel(np, ((i * 256 / np->numPixels()) + j) & 255));
    }
    np->show();
    delay(wait);
  }
}

void rainbow(Adafruit_NeoPixel * np, uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256; j++) {
    for(i=0; i<np->numPixels(); i++) {
      np->setPixelColor(i, Wheel(np, (i+j) & 255));
    }
    np->show();
    delay(wait);
  }
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(Adafruit_NeoPixel * np, byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    return np->Color(255 - WheelPos * 3, 0, WheelPos * 3,0);
  }
  if(WheelPos < 170) {
    WheelPos -= 85;
    return np->Color(0, WheelPos * 3, 255 - WheelPos * 3,0);
  }
  WheelPos -= 170;
  return np->Color(WheelPos * 3, 255 - WheelPos * 3, 0,0);
}

uint8_t red(uint32_t c) {
  return (c >> 16);
}
uint8_t green(uint32_t c) {
  return (c >> 8);
}
uint8_t blue(uint32_t c) {
  return (c);
}
