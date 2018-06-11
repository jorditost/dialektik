/*
  Linear Actuator Functions
*/

void SetStrokePerc(float strokePercentage) {
  if ( strokePercentage >= 1.0 && strokePercentage <= 99.0 ) {
    int usec = 1000 + strokePercentage * ( 2000 - 1000 ) / 100.0 ;
    myServo.writeMicroseconds( usec );
  }
}

void SetStrokeMM(int strokeReq,int strokeMax) {
  SetStrokePerc( ((float)strokeReq) / strokeMax );
}
