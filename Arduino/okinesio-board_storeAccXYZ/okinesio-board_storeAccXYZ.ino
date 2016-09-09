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

#include <Arduino.h>
#include <SPI.h>

#include <avr/pgmspace.h>

int16_t slaveSelectPin = 17; // pin 17 is used

const PROGMEM  uint16_t acc_x[10000];

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
  initBMI160();

  delay(1500);
  
  // say hello
  Serial.println(">> okinesio - activity tracking module <<\n");
}

void loop()
{
  struct accelData acc;
  imuGetAccelData(&acc);
  
  // Print accelerometer data (X, Y and Z)
  /*
  Serial.print("ACC:\t");
  Serial.print(acc.x);
  Serial.print("\t");
  Serial.print(acc.y);
  Serial.print("\t");
  Serial.print(acc.z);
  Serial.println("\t\t");
  */
  
  // Delay for better readability of serial monitor
  delay(50);
}
