/********************************************************************************

  Sample code to get the accelerometer data (X,Y and Z) from the sensor.
  Copyright (C) 2016 okinesio
  http://okinesio.org


  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License along with
  this program. If not, see <http://www.gnu.org/licenses/>.

********************************************************************************/

#include <Arduino.h>
#include <SPI.h>
#include <Time.h>

int16_t slaveSelectPin = 17; // pin 17 is used

struct accelData {
  int16_t x;
  int16_t y;
  int16_t z;
};

int minutes = 0;
int stepsperminute[300];
long stepstimecode[300];

int lastmin = -1;

uint8_t c = 0; // counted steps

void setup() {

  // Set the SS pin
  pinMode(slaveSelectPin, OUTPUT);
  digitalWrite(slaveSelectPin, HIGH);

  // Init SPI
  SPI.begin();

  // Init Serial
  Serial.begin(115200);
  delay(100);

  // Init BMI160 (accelerometer)
  initBMI160();

  delay(1500);

  // say hello
  Serial.println(">> okinesio - activity tracking module <<\n");

  digitalWrite(13, HIGH);
}

void loop()
{
  //struct stepsperminute steps;
  //steps.
  // Sync clock
  /*
    if (Serial.available()) {
    //processMessages();
    }
  */
  while (Serial.available()) {
    processMessages();
  }

  // Get current steps

  /*
    Serial.print(now());
    Serial.print("\tSTEPS:\t");
    Serial.println(getStepCount());
  */
  //Serial.print(".");


  if (lastmin != minute())
  {
    // Save steps in array and set timecode
    stepsperminute[minutes] = getStepCount();
    stepstimecode[minutes] = now();
    minutes ++;

    // Reset step counter every minute and store values
    uint8_t cData[1] = {0xB2};
    spiBurstWrite(0x7E, cData, 1);
    microPause();

    lastmin = minute();

    digitalWrite(13, HIGH);
    delay(20);
    digitalWrite(13, LOW);

    Serial.println("");
    Serial.print("Update: ");
    Serial.print(hour());
    Serial.print(":");
    Serial.print(minute());
    Serial.print(":");
    Serial.print(second());
    Serial.print("\t");
    Serial.print(getStepCount());
    Serial.println("");
  }


  // Get current step count (updates only if a step is counted)
  /*
    if (c != getStepCount()) {
     Serial.print("STEPS:\t");
     Serial.println(getStepCount());
     c = getStepCount();
    }
  */

  // Delay for better readability of serial monitor
  //delay(100);
}

void processMessages() {
  unsigned long pctime;
  const unsigned long DEFAULT_TIME = 1357041600; // Jan 1 2013

  byte incomingByte = Serial.read();
  
  if (incomingByte == 'T') { //(Serial.find("T")) {
    pctime = Serial.parseInt();
    if ( pctime >= DEFAULT_TIME) { // check the integer is a valid time (greater than Jan 1 2013)
      setTime(pctime); // Sync Arduino clock to the time received on the serial port
    }
    int lastmin = -1;
  }
  else if (incomingByte == 'C') { //(Serial.find("C")) {
    Serial.println("");
    Serial.print(minutes);
    Serial.print(" / ");
    Serial.print(hour());
    Serial.print(":");
    Serial.print(minute());
    Serial.print(":");
    Serial.print(second());
    Serial.print("\t");
    Serial.print(getStepCount());
    Serial.println("");
  }
  else if (incomingByte == 'S') { //(Serial.find("S")) {
    Serial.println("All steps:");
    for (int i = 0; i < 299; i++)
    {
      if (stepstimecode[i] <= 0)
      {
        break;
      }
      Serial.print(stepstimecode[i]);
      Serial.print("\t");
      Serial.println(stepsperminute[i]);
    }
  }

}
void serialEvent() {
  while (Serial.available()) {
    processMessages();
  }
}
