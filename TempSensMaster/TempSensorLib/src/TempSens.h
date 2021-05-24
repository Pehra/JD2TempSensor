/******************************
	This librry is for the hands free temperature sensor project
	
	Authors:
		Kaleb Krieger 
		Andrew Pehrson 
		Quentin Onyemordi
		
******************************/

#include <Wire.h>             		//Allows the hardware implementation with microcontroller
#include <Adafruit_MLX90614.h>      //Includes Adafruit library designed for the Temp. Sensor (MLX90614)
#include <ESP8266WiFi.h>            //Allows ESP8266 to connect to WiFi
#include <time.h>					//Allows time to be calculated via WiFi
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define BuzzerPin 12
#define FeverTemp 100.4
#define SCREEN_ADDRESS 0x3C 		//Sets the screen address
#define OLED_RESET     4 			// Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_WIDTH 128 			// OLED display width, in pixels
#define SCREEN_HEIGHT 32 			// OLED display height, in pixels

/**
  *	Class to controle the temprature sensor modual
  *
  */
class TempSens {
public:
	double Temp, Fever_Temp;
	bool Sick;
	const char* ssid;
	const char* password;
	String apiKey;   
    WiFiClient client;	
	
	TempSens();
	void putSleep();
	void wakeUp(int type);
	void sendData();
	void tempCalc();
	float getTemp();
	void liveRead(int time);
	void displaySick();
	
private:
	Adafruit_MLX90614 mlx;
	Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET); //Creates the display operator for the display 
	
	void initGoogleSheet();
	void initWifi();
	void initThingSpeak();
	void initTemp();
	void initOLED();
	void soundFever();
	void soundOK();
	void Welcome_Message();
	void Instructions_for_user();
	void Letting_user_know_temp_is_being_taken();
 };
