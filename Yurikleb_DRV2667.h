/*
  Yurikleb_DRV2667.h - Library for controling the TI - DRV2667 Hapic Piezo Driver
  Created by Yuri Klenaov, January, 2016. (yurikleb.com)
  Released into the public domain.
  For more information see the DRV2667 Datasheet http://www.ti.com/lit/ds/symlink/drv2667.pdf
*/

#ifndef Yurikleb_DRV2667_h
#define Yurikleb_DRV2667_h


#if ARDUINO >= 100
 #include "Arduino.h"
#else
 #include "WProgram.h"
#endif

#include <Wire.h> //Wire Library to use I2C 

#define DRV2667_ADDR 0x59 //The DRV2667 Chip default I2C address.

class Yurikleb_DRV2667
{
  public:
    Yurikleb_DRV2667(void);
    void begin(void);

	void playWave(byte WaveForm[][4], byte WavesNumber);
	void setToAnalogInput();
	void writeRegisterBytes(byte reg, byte val);
	void i2c_Scan(void);
	

  private:

};

#endif

