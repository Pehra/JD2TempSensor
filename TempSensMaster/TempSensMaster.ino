#include "TempSens.h"
TempSens TempSens_0;

void setup() {
    
  Serial.begin(115200); // Initialize Serial to log output
  Serial.println();
  Serial.println("Serial started...");
  
  Wire.begin(); //Joing I2C bus
  
  TempSens_0.wakeUp(1);
  
  TempSens_0.initOLED();
  TempSens_0.Welcome_Message();
    
  TempSens_0.initTemp();

  TempSens_0.Loading();
  TempSens_0.initWifi();
  
  TempSens_0.Instructions_for_user();
  TempSens_0.liveRead(25);
  TempSens_0.getTemp();
  TempSens_0.displaySick();
  TempSens_0.sendTempData();
  TempSens_0.putSleep();
  

}

void loop() {
  TempSens_0.testOled();

}
