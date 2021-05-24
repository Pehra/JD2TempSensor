/******************************
	This librry is for the hands free temperature sensor project
	
	Authors:
		Kaleb Krieger 
		Andrew Pehrson 
		Quentin Onyemordi
		
******************************/

#include "TempSens.h"

/*

*/
TempSens::TempSens(){
	
}

void TempSens::putSleep(){
	
}

void TempSens::wakeUp(int type){
	
}

void TempSens::sendData(){
	
}

double TempSens::getTemp(){
	
}

void TempSens::liveRead(int time){
	
}

void TempSens::displaySick(){
	
}
	
void TempSens::initWifi(){
	
}

void TempSens::initThingSpeak(){
	
}

void TempSens::initTemp(){
	
}

/****************************************************
*Function that initializes the OLED
****************************************************/
void TempSens::initOLED(){
	Serial.begin(9600);

	  //Starts up the screen
	if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS))
	{
		Serial.println(F("SSD1306 allocation failed"));
		for (;;); // Don't proceed, loop forever
	}

	// Show initial display buffer contents on the screen --
	// the library initializes this with an Adafruit splash screen.
	delay(500); // Pause for 0.5 seconds

	//Cleares the display
	display.clearDisplay();
}

void TempSens::soundFever(){
	
}

void TempSens::soundOK(){
	
}

/***********************************************************
 * Function that creates a welcome message
 **********************************************************/
void TempSens::Welcome_Message() {
	//Creates the inital greeting for the user
	display.setTextSize(2);
	display.setTextColor(WHITE);
	display.setCursor(20, 10);
	display.println("Welcome!");
	display.display();
	delay(2000);//Pauses for 2 seconds
	display.clearDisplay();
}

/***********************************************************
 * Function that displays a set of diresctions for the user
 **********************************************************/
void TempSens::Instructions_for_user(); {
//Block this in with the above set to be triggered by the motion module 
//Creates instreuctions for the user to follow  
	display.setTextSize(1);
	display.setTextColor(WHITE);
	display.setCursor(0, 10);
	display.print("Please ");
	display.print("stand in");
	display.print("front of ");
	display.print("the sensor.");
	display.display();
	delay(4000);
	display.clearDisplay();
}

/***********************************************************
 * Function that displays that the users temp will be taken
 **********************************************************/
void TempSens::Letting_user_know_temp_is_being_taken(); {
	display.setTextSize(1);
	display.setTextColor(WHITE);
	display.setCursor(0, 10);
	display.print("Taking ");
	display.print("your");
	display.print("tempature ");
	display.print("now:");
	display.display();
	delay(1000);
	display.clearDisplay();
}
