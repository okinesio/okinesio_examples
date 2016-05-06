/********************************************************************************
* 
* Sample code to get the accelerometer data (X,Y and Z) from the sensor.
* Copyright (C) 2016 okinesio
* http://okinesio.org
*
*
* This program is free software; you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation; either version 3 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License along with
* this program. If not, see <http://www.gnu.org/licenses/>.
*
********************************************************************************/


#include <Streaming.h>
#include <Arduino.h>
#include <SPI.h>

int16_t slaveSelectPin = 17; // pin 17 is used 

struct accelData {
  int16_t x;
  int16_t y;
  int16_t z;
};

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
  imuBMI160();

  delay(500);
  // Print the chip ID
  Serial << "Chip ID: " << imuGetChipId() << endl;
}

void loop()
{
  // Get current steps
  Serial << "STEPS:\t" << getStepCount() << endl;

  
  // Get current step count (updates only if a step is counted)
  /*
  if (c != getStepCount()) {
    Serial << "STEPS:\t" << getStepCount() << endl;
    c = getStepCount();
  }
  */
  
  // Delay for better readability of serial monitor
  delay(100);
}
