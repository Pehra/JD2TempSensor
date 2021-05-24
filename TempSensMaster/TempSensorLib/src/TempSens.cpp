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

/****************************************************
*This function uses the public bool sick,
*if it is true it will run the sound for a fever
*if it is false then it will non fever sound
****************************************************/
void TempSens::displaySick(){
	if(Sick == True){//Checks to see if Sick is true 
		soundFever();//Plays the Fever sound function
	}
	else{
		soundOK();//Plays the non fever sound function
	}
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

/*************************************************************************************************
 * Function that generates a tone played by the buzzer when the temp is above the fever limit
 *************************************************************************************************/
void TempSens::soundFever(){
	for(int i = 0; i < 4; i++)
	{
		tone(buzzer, 3000);//Sends a 3KHz sound signal to the buzzer
		delay(500); //wait hald a second
	}
}

/*********************************************************************************************
 * Function that generates a tone played by the buzzer when the temp is below the fever limit
 *********************************************************************************************/
void TempSens::soundOK(){
		
		tone(buzzer, 460);//Sends a 460Hz sound signal to the buzzer
		delay(500); //wait hald a second
		tone(buzzer, 700);//Sends a 700Hz sound signal to the buzzer
		delay(750); //wait hald a second
		tone(buzzer, 1100);//Sends a 1.1KHz sound signal to the buzzer
		delay(1000); //wait hald a second

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
