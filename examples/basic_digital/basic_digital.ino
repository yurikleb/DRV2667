#include <Wire.h> //Include arduino Wire Library to enable to I2C
#include "Yurikleb_DRV2667.h"

Yurikleb_DRV2667 drv;

//****** SAMPLE WAVE FORMS *******

// WaveForm Array: [Amplitude, Freq, Cycles, Envelope] 
// Amplitude    --  min:0=50v max: 255=100v 
// Frequerncy   --  0-255 or 0x00-0xFF
// Duration     --  Cycles 0-255
// Envelope     --  (Ramp up + down)
// Max 60 waves per array !!

byte WaveForm_1[4][4] = { 
                      {255, 0x15, 50, 0x09},
                      {255, 0x17, 50, 0x09},
                      {255, 0x19, 50, 0x09},
                      {255, 0x1B, 50, 0x09}                    
                      };

byte WaveForm_2[6][4] = { 
                      {255, 0x15, 50, 0x09},
                      {255, 0x17, 50, 0x09},
                      {255, 0x19, 50, 0x09},
                      {255, 0x1B, 50, 0x09}, 
                      {255, 0x1D, 50, 0x09},
                      {255, 0x1F, 50, 0x09}                      
                      };

byte WaveForm_3[2][4] = { 
                      {255, 0x15, 50, 0x09},
                      {255, 0x17, 50, 0x09}
                      };

byte WaveForm_4[1][4] = { 
                      {255, 0x15, 50, 0x09}                     
                      };

//****** END OF WAVEFORMS ******

void setup() {

  delay(10);
  Serial.begin(9600);
  Serial.println("DRV2667 test!");

  
  drv.begin();  
//drv.setToAnalogInput();  //Swithch To Analog

}

void loop() {  
      drv.playWave(WaveForm_3, sizeof(WaveForm_3)); //Play one the Waveforms defined above;
      delay(3000); //Wait for the wave to play;  
}
