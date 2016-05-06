/****************************************************************************
* Copyright (C) 2011 - 2015 Bosch Sensortec GmbH
*
* bmi160_example.ino
* Date: 2015/12/08
*
* Usage:        Example code for getting started with the BMI160 for 
*               okinesio.org 
*
****************************************************************************
/***************************************************************************
* License:
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions are met:
*
*   Redistributions of source code must retain the above copyright
*   notice, this list of conditions and the following disclaimer.
*
*   Redistributions in binary form must reproduce the above copyright
*   notice, this list of conditions and the following disclaimer in the
*   documentation and/or other materials provided with the distribution.
*
*   Neither the name of the copyright holder nor the names of the
*   contributors may be used to endorse or promote products derived from
*   this software without specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
* ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
* WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
* DISCLAIMED. IN NO EVENT SHALL COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY
* DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
* (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
* LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
* ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
* (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
* SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE
*
* The information provided is believed to be accurate and reliable.
* The copyright holder assumes no responsibility for the consequences of use
* of such information nor for any infringement of patents or
* other rights of third parties which may result from its use.
* No license is granted by implication or otherwise under any patent or
* patent rights of the copyright holder.
*/

void imuGetAccelData(struct accelData *localAccelData)
{
  uint8_t data[6];
  spiBurstRead(0x12, data, 6); // Read 6 databytes from the accelerometer register
  localAccelData->x = (int16_t)(data[1] << 8) + (int16_t)data[0];
  localAccelData->y = (int16_t)(data[3] << 8) + (int16_t)data[2];
  localAccelData->z = (int16_t)(data[5] << 8) + (int16_t)data[4];
}

uint8_t imuGetChipId(void)
{
  uint8_t data = 0;
  spiBurstRead(0x00, &data, 1);
  return data;
}

void imuInit(void)
{
  uint8_t data = 0;
  
  // Soft Reset
  data = 0xB6;
  imuSetCommandRegister(data);
  microPause();

  // Prevent the gyroscope wake-up
  data = 0;
  spiBurstWrite(0x6C, &data, 1);
  microPause();

  // Set acc_pmu_mode to Normal Mode (0b00010001) in CMD register for full chip operation
  data = 0x11;
  imuSetCommandRegister(data);
  microPause();
}



void imuSetCommandRegister(uint8_t data)
{
  spiBurstWrite(0x7E, &data, 1); //Write to the command register
}


void spiBurstWrite(uint8_t regAddress, uint8_t *regValue, uint8_t count)
{
  //Generic write function
  SPI.beginTransaction(SPISettings(500000, MSBFIRST, SPI_MODE0));
  digitalWrite(slaveSelectPin, LOW);
  SPI.transfer(regAddress & ~0x80);  // 7 bit addressing and MSB low to signify write
  for (uint8_t i = 0; i < count; i++)
  {
    SPI.transfer(regValue[i]);
  }
  digitalWrite(slaveSelectPin, HIGH);
  SPI.endTransaction();
  microPause();
}

void spiBurstRead(uint8_t regAddress, uint8_t *regValue, uint8_t count)
{
  //Generic read function
  SPI.beginTransaction(SPISettings(500000, MSBFIRST, SPI_MODE0));
  digitalWrite(slaveSelectPin, LOW);
  SPI.transfer(regAddress | 0x80);  // 7 bit addressing and MSB high to signify read
  for (uint8_t i = 0; i < count; i++)
  {
    regValue[i] = SPI.transfer(0x00);
  }
  digitalWrite(slaveSelectPin, HIGH);
  SPI.endTransaction();
  microPause();
}

void microPause(void)
{
  delayMicroseconds(500);
}
