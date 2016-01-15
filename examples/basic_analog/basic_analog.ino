#include <Wire.h> //Include arduino Wire Library to enable to I2C
#include "Yurikleb_DRV2667.h"

Yurikleb_DRV2667 drv;

void setup() {

  delay(10);
  Serial.begin(9600);
  Serial.println("DRV2667 test!");

  
  drv.begin();  
  drv.setToAnalogInput();  //Swithch To Analog

}

void loop() {  

}
