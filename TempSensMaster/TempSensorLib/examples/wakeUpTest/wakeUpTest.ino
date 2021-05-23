/*
 * File name: wakeUpTest.ino
 * Auther: Andrew Pehrson
 * Operatons: This code is for testing the circuitry for the PIR motion sensor 
 *            and the deep sleep mode of the esp8266
 */
#include <ESP8266WiFi.h>

void Blink();

/*
 * Function: Setup
 * assumptions: Will run at every wakeup
 * Operations: initializes variables, and calls functions to give desired
 *             interactions.
 */
void setup() {
  //initalizations
  int start = millis();
  pinMode(BUILTIN_LED, OUTPUT);
  Serial.begin(115200);
  
  //restart reason
  Serial.println(""); Serial.print("Reason startup :");Serial.println(ESP.getResetReason());
  //waking time
  Serial.println("Waking time: ");Serial.print(millis()-start);Serial.println("ms");

  Blink();

  //Gose into deep sleep mode
  Serial.println("Going to deep sleep");
  ESP.deepSleep(0);   
}

//Stays empty sine no tasks repeat
void loop() {   
}

/*
 * Funtion: Blink()
 * Assumptions: BUILTIN_LED is a pin conected to an LED
 * Operations: Blinks LED to indicate somthing is happening
 */
void Blink(){
  digitalWrite(BUILTIN_LED, HIGH);
  delay(1000);
  digitalWrite(BUILTIN_LED, LOW);
}
