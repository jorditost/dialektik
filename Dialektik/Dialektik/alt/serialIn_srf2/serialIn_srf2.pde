import processing.serial.*;

String buff = "";
int val = 0;
int NEWLINE = 10;

Serial port;

void setup()
{
  size(200, 200);

  // Print a list in case COM1 doesn't work out
  println("Available serial ports:");
  println(Serial.list());

  //port = new Serial(this, "COM1", 19200);
  // Uses the first available port

  port = new Serial(this, Serial.list()[3], 19200); //port = new Serial(this, "COM1", 19200) - bei mir ist es 3
  
}

void draw()
{
  while (port.available() > 0) {
    serialEvent(port.read());
  }
  background(val);
}
void serialEvent(int serial) 
{ 
  // If the variable "serial" is not equal to the value for 
  // a new line, add the value to the variable "buff". If the 
  // value "serial" is equal to the value for a new line,
  //  save the value of the buffer into the variable "val".
  if(serial != NEWLINE) { 
    buff += char(serial);
  } else {
    buff = buff.substring(0, buff.length()-1);
    // Parse the String into an integer
    val = Integer.parseInt(buff);
    println(val);
    // Clear the value of "buff"
    buff = "";
  }
}

