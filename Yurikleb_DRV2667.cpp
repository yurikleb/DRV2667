/*
  Yurikleb_DRV2667.h - Library for controling the TI - DRV2667 Hapic Piezo Driver
  Created by Yuri Klenaov, January, 2016. (yurikleb.com)
  Released into the public domain.
*/

#if ARDUINO >= 100
 #include "Arduino.h"
#else
 #include "WProgram.h"
#endif

#include <Wire.h> //Wire Library to use I2C

#include "Yurikleb_DRV2667.h"

Yurikleb_DRV2667::Yurikleb_DRV2667(){
}

void Yurikleb_DRV2667::begin() {
  Wire.begin();
  Serial.begin (9600);
  i2c_Scan(); // Scan for i2c devices to make sure we have the DRV2667 attached;
  delay(300);
}


//Send a Wave to the DRV2667
void Yurikleb_DRV2667::playWave(byte WaveForm[][4], byte WavesNumber) {

  Serial.println("Playing WaveForm:");
  Serial.print("Containing: "); Serial.print(WavesNumber / 4); Serial.println(" waves:");
  for (int j=0; j < WavesNumber/4; j++){
    Serial.print("Ampl: "); Serial.print(WaveForm[j][0]);  Serial.print("  |  Freq: "); Serial.print(WaveForm[j][1]);    Serial.print("  |  Duration: "); Serial.print(1000 * (WaveForm[j][2] / (7.8125 * WaveForm[j][1]))); Serial.print("ms");  Serial.print("  |  Env: 0x"); Serial.println(WaveForm[j][3], HEX);
  }
  Serial.println("");
  //control
  writeRegisterBytes(0x02, 0x00); //Take device out of standby mode
  writeRegisterBytes(0x01, 0x03); //Set Gain 0-3 (0x00-0x03 25v-100v)
  writeRegisterBytes(0x03, 0x01); //Set sequencer to play WaveForm ID #1
  writeRegisterBytes(0x04, 0x00); //End of sequence
  //header
  writeRegisterBytes(0xFF, 0x01); //Set memory to page 1
  writeRegisterBytes(0x00, 0x05); //Header size –1
  writeRegisterBytes(0x01, 0x80); //Start address upper byte (page), also indicates Mode 3
  writeRegisterBytes(0x02, 0x06); //Start address lower byte (in page address)
  writeRegisterBytes(0x03, 0x00); //Stop address upper byte
  writeRegisterBytes(0x04, 0x06+WavesNumber-1); //Stop address Lower byte
  writeRegisterBytes(0x05, 0x01); //Repeat count, play WaveForm once
  
  //WaveForm Data From the array
  for(byte i = 0; i < WavesNumber; i++){
    writeRegisterBytes(0x06+i*4+0, WaveForm[i][0]); 
    writeRegisterBytes(0x06+i*4+1, WaveForm[i][1]); 
    writeRegisterBytes(0x06+i*4+2, WaveForm[i][2]); 
    writeRegisterBytes(0x06+i*4+3, WaveForm[i][3]);
  }
  
  //Control
  writeRegisterBytes(0xFF, 0x00); //Set page register to control space
  writeRegisterBytes(0x02, 0x01); //Set GO bit (execute WaveForm sequence)ss
  
  //delay( 1000 * (cycles / (7.8125 * frequency)) );

}

void Yurikleb_DRV2667::setToAnalogInput(){
  Serial.println("Switching to Analog Input Mode");
  //control
  writeRegisterBytes(0x02, 0x00); //Take device out of standby mode
  writeRegisterBytes(0x01, 0x07); //Set to analog input + Gain 0-3 (0x04-0x07 25v-100v)
  writeRegisterBytes(0x02, 0x02); //Set EN_OVERRIDE bit = boost and amplifier active


}

//Write Bytes via I2c (Using Wire Library)
void Yurikleb_DRV2667::writeRegisterBytes(byte reg, byte val) {
  Wire.beginTransmission(DRV2667_ADDR);
  Wire.write((byte)reg);
  Wire.write((byte)val);
  Wire.endTransmission();
}

void Yurikleb_DRV2667::i2c_Scan(){
  // Leonardo: wait for serial port to connect
  while (!Serial)
  {
  }

  Serial.println ();
  Serial.println ("I2C scanner. Scanning ...");
  byte count = 0;

  Wire.begin();
  for (byte i = 8; i < 120; i++)
  {
    Wire.beginTransmission (i);
    if (Wire.endTransmission () == 0)
    {
      Serial.print ("Found address: ");
      Serial.print (i, DEC);
      Serial.print (" (0x");
      Serial.print (i, HEX);
      Serial.println (")");
      count++;
      delay (1);
    }
  }
  Serial.println ("Done.");
  Serial.print ("Found ");
  Serial.print (count, DEC);
  Serial.println (" device(s).");
  Serial.println ("***********");  
  Serial.println (" ");
  
}