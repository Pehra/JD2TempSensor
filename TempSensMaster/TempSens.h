/******************************
	This librry is for the hands free temperature sensor project
	
	Authors:
		Kaleb Krieger 
		Andrew Pehrson 
		Quentin Onyemordi
		
******************************/
#ifndef TEMPSENS_H
#define TEMPSENS_H

//#include "TempSens.cpp"
#include <Wire.h>            	  //I2C library, required for MLX90614
#include <SparkFunMLX90614.h>   //Click here to get the library: http://librarymanager/All#Qwiic_IR_Thermometer by SparkFun
#include <ESP8266WiFi.h>        //Allows ESP8266 to connect to WiFi
#include <time.h>				        //Allows time to be calculated via WiFi
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define BuzzerPin 		12
#define FeverTemp 		100.4
#define SCREEN_ADDRESS 	0x3C 	//Sets the screen address
#define OLED_RESET		4 		// Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_WIDTH 	128 	// OLED display width, in pixels
#define SCREEN_HEIGHT 	32 		// OLED display height, in pixels
#define True 1
#define False 0

/**
  *	Class to controle the temprature sensor modual
  *
  */
class TempSens {
public:
	float Temp;
	bool Sick;  	
	
	TempSens();
	void Init();
	void putSleep();
	void wakeUp(int type);
	void sendData();
	float getTemp();
	void liveRead(unsigned long timer);
	void displaySick();
	void testTempSensor();
	void testBuzer();
	void testOled();
	
private:
	const char* ssid = "esp8266";
	const char* password = "12345678";
	String apiKey = "1Y9IDJKPYM654Z82"; 
  const char* server = "api.thingspeak.com"; 
  
	WiFiClient client;
	IRTherm therm; 				
	Adafruit_SSD1306 display; //Creates the display operator for the display 
	
	void initWifi();
	void initThingSpeak();
	void initTemp();
	void initOLED();
	void soundFever();
	void soundOK();
	void Welcome_Message();
	void Instructions_for_user();
	void Letting_user_know_temp_is_being_taken();
	void tempCalc();
 };
#endif
