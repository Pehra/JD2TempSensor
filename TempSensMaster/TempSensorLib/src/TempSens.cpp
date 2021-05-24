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
	
	if (client.connect(server,80))   //   "184.106.153.149" or api.thingspeak.com
 {  
   
   String postStr = apiKey;
   postStr +="&field1=";
   postStr += String(Temp);
   postStr += "\r\n\r\n";
   client.print("POST /update HTTP/1.1\n");
   client.print("Host: api.thingspeak.com\n");
   client.print("Connection: close\n");
   client.print("X-THINGSPEAKAPIKEY: "+apiKey+"\n");
   client.print("Content-Type: application/x-www-form-urlencoded\n");
   client.print("Content-Length: ");
   client.print(postStr.length());
   client.print("\n\n");
   client.print(postStr); 


  Serial.println();
 }
    client.stop();
  
    delay(3000);
}

double TempSens::getTemp(){
	
	const int Avg = 25;                                         // Number of readings to average
    double OF[Avg];                                             // Array to store readings for Object temp in F
	
	for(int y = 0; y < Avg; y++){
        OF[y] = mlx.readObjectTempF();                          // reads temp values
      }
    
      for(int j = 0; j < Avg-1; j++){
        Temp += OF[j];
      }
    
      Temp = Temp / Avg;                                // Divide by total number of readings for average
    
	return Temp;
}

void TempSens::liveRead(int time){
	
}

void TempSens::displaySick(){
	
}
	
void TempSens::initWifi(){
  
  Serial.begin(115200);                                                         //Initializes data rate in bits/s for microcontroller (esp8266)                            


   WiFi.mode(WIFI_STA);                       
   WiFi.begin (ssid, password);                                                 //Starts wifi connection           
  
   mlx.begin();  
}

void TempSens::initThingSpeak(){
	
}

void TempSens::initTemp(){
	
	apiKey = "1Y9IDJKPYM654Z82";                                       //Write API key from ThingSpeak
	ssid = "esp8266";                                                  //Wifi SSID
	password = "12345678";                                             //Wifi Password
	server = "api.thingspeak.com";
	Fever_Temp = 100.4;                                                //Double that holds value for temperature that classifies as too high
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

void TempSens::tempCalc(){
	
	if(Temp < Fever_Temp){  //If statement to determine if the temp is lower than 100.4 degrees farenheit. Defines bool for OLED as false
    Sick = false;
    Serial.println("Temperature is acceptable");
  }
  else{                       //Else to determine if temp is higher than 100.4 farenheit. Defines bool for OLED as true
    Sick = true;
    Serial.println("Temperature is too high");
  }

}

