import processing.serial.*;

Serial myPort;

void setup()
{
  println(Serial.list());
  myPort = new Serial(this, Serial.list()[0], 115200);
  
  myPort.write(new java.util.Date().getTime()+"");
  
  String myString = myPort.readStringUntil(10);
}

void draw()
{
  long t = new java.util.Date().getTime();
  
  while (myPort.available() > 0)
  {
    String t_in = myPort.readStringUntil(10);
    if (myString != null) {
      println(myString);
    }
  }
}