//import processing.opengl.*;
import processing.serial.*;
import krister.Ess.*;

boolean debug = false;

// How often do you want to measure the input (this is the internal Processing frame rate )
int SENSE_RATE = 2;

// What is the maximum display output cycles per second
int DISPLAY_RATE = 16;

int FRAME_RATE = 16;

// Trim values to set minimum and maximum ranges (will be about actual distances in cm's / 29)
// The position of the golden cut will be worked out as relative to these two points
// What is the base line sensor value which you want to count as being 0
int TRIM_MIN = 16;
// What is the maximum sensor value which you want to measure to
int TRIM_MAX = 1200; 

// Golden Ratio
float PHI = 1 - 0.618;

int counter = 0;



//////////////////////////
// dialektik            //
// -------------------- //
// 08 March 2006        //
// studio contraire     //
//////////////////////////

boolean state = false;
float currentRate;
int delayTime;
float tempo; //audiotempo for timeshift
Serial port; //setzt port als variable f�r den SerialPort

AudioChannel mySoundA, mySoundB;
SineWave myWaveA;
PinkNoise myPNoise;
Envelope myEnvelope;
TempoShift myTempoShift;
HighPass myHighPass;
LowPass myLowPass;

void setup()
{
  if (debug) {
    println("setup(): reading from serial at rate: " + SENSE_RATE);
    println("setup(): available serial ports: ");  // Print a list in case COM1 doesn't work out
    println(Serial.list()); 

  }
  
  //set fullscreen
  
  frame.setUndecorated(true);   
  GraphicsDevice gd = GraphicsEnvironment.getLocalGraphicsEnvironment().getDefaultScreenDevice();
  gd.setFullScreenWindow(frame);

  // Set up the input port
  port = new Serial(this, Serial.list()[3], 19200); //port = new Serial(this, "COM1", 19200) - bei mir ist es 3

  framerate(FRAME_RATE);
  size(600,600);   
  background (255, 255, 255); 
  fill (0, 0, 0);
  stroke (255);

  Ess.start(this);
  Ess.masterVolume(1);

  mySoundA=new AudioChannel();
  mySoundA.initChannel(mySoundA.frames(700));

  mySoundB=new AudioChannel();
  mySoundB.initChannel(mySoundA.frames(700));

  myWaveA=new SineWave(180,.8);
  myWaveA.generate(mySoundA,0,mySoundA.frames(700));

  myPNoise=new PinkNoise(.9);
  myPNoise.generate(mySoundB,0,mySoundB.frames(700));    

  EPoint[] env=new EPoint[2]; // set envelope points
  env[0]=new EPoint(0,0);
  env[1]=new EPoint(.05,8);

  myEnvelope=new Envelope(env);
  //  myEnvelope.filter(mySoundA);
  myEnvelope.filter(mySoundB);  

  //myLowPass=new LowPass(3500,-15,5);
  //myLowPass.filter(mySoundA);

  myHighPass=new HighPass(960,-10,16);
  myHighPass.filter(mySoundB);

}


void draw() 
{ 
  if (counter == 0 || counter == 10){
    int in = getData();
    float coefficient = normalise(in);
    currentRate = getRate(coefficient);
  }

  int displayRate; //has to be manually adjusted to the FRAME_RATE

  if (currentRate < 2) {
    displayRate = 1;
    tempo = 1;
  } 
  else if (currentRate < 3) {
    displayRate = 2;
    tempo = .5;
  } 
  else if (currentRate < 7) {
    displayRate = 4;
    tempo = .25;
  } 
  else if (currentRate < 12 ) {
    displayRate = 8; 
    tempo = .125;
  } 
  else {
    displayRate = 16;
    tempo = .1;
  }

  if (debug) {
    println( "The display rate is " + displayRate); 
  }  

  int delayTime = int(960 / displayRate);
  //println("delay is:" + delayTime);

  //check counter whether it can be divided by number of outputs per second
  int changer = (counter%(FRAME_RATE/displayRate)); 
  if (changer == 0) {  
    change();
    /*
    // change duration of sound
     myTempoShift=new TempoShift(tempo);    
     myTempoShift.filter(mySoundA,0,mySoundA.frames(300));    
     myTempoShift.filter(mySoundB,0,mySoundB.frames(300));      
     */
    delay(delayTime);
  }

  //Counter has to start with 1, not 0, due to the % in the changer
  if (counter == FRAME_RATE+1) {
    /* if (debug) {
     println("Counter resetting");
     }*/
    counter = 1;
  } 
  else {
    if (debug) {
      println("Counter is " + counter); 
    }
    counter++;
  }

}

