

public int getData() {
 
  String data = "0";
  
  if (port.available() != 0) {
    String inData = port.readString();
    if (inData != null) {
       String[] inElements = inData.split("\n");
       if (inElements != null && inElements.length != 0) {
         data = inElements[inElements.length-1];
       }
    }
  } else {
    println("getData(): USB board looks dead"); 
  }
 
  int retInt = 0;
  try {
    retInt = Integer.parseInt(data);
  } catch (NumberFormatException nfe) {
    // println("getData(): failed to parse string: " + data + " to int");
  }

  if (debug) {
   println("getData(): current sensor input: " + retInt);
  } 

  return retInt;
}



public float normalise(int inData) {
  
  if(inData < TRIM_MIN) {
    if (debug) {
     println("normalise(): low value " + inData + " rebased to minimum " + TRIM_MIN);
    } 
    inData = TRIM_MIN;
  }
  
  if (inData > TRIM_MAX) {
    if (debug) {
     println("normalise(): high value " + inData + " rebased to maximum " + TRIM_MAX);
    } 
    inData = TRIM_MAX;
  }
  
  float rebased = inData - TRIM_MIN;
  float diff = TRIM_MAX-TRIM_MIN;
  float normalised = rebased / diff;
  
  if (debug) {
   println("normalise(): input value: " + inData + " rebased to: " + normalised);
  } 
  
  return normalised;
  
}



public float getRate(float coefficient) {
 
  float rate;
  
  if (coefficient < PHI) {
    rate = 1 + ((coefficient / PHI ) * ( DISPLAY_RATE - 1 ));
  } else {
    float relPos = (coefficient - PHI) / (1 - PHI);
    rate =  1 + ((1 - relPos) * (DISPLAY_RATE - 1));
  }
  
  if (debug) {
   println("getRate(): coefficent value: " + coefficient + " means rate of : " + rate);
  } 
  
  return rate;
  
}
