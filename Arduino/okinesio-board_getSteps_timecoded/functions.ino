/********************************************************************************
*
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


void initBMI160(void)
{
  // init IMU
  imuInit();
  
  /* Enable specific interupts/functions */
  
  uint8_t data = 0;
  
  // enable step counter in normal mode
  uint8_t cData[2] = {0x15, 0x0B};
  spiBurstWrite(0x7A, cData, 2);
  microPause();
}


// get current steps
int16_t getStepCount(void)
{
  uint8_t data[2];
  spiBurstRead(0x78, data, 2); // 0x78 = step count, 0x79 = multiplier
  
  int16_t steps = (int16_t)data[0] + ((int16_t)data[1] * 255);
  return steps;
}




