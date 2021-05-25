/*******************************************************************************
This librry is for the hands free temperature sensor project
	
	Authors:
		Kaleb Krieger 
		Andrew Pehrson 
		Quentin Onyemordi
		
*******************************************************************************/

#include "TempSens.h"

/*******************************************************************************
*
*******************************************************************************/
TempSens::TempSens(){
	Init();
}

/*******************************************************************************
*
*******************************************************************************/
void TempSens::Init(){
	initWifi();
	initTemp();
	initOLED();
}

/*******************************************************************************
	putSleep(void) should put the OLED display, the MLX IR seonsor,
	and ESP to low-power sleep mode. In this mode the device is 
	expected to only pull 36uA. 
*******************************************************************************/
void TempSens::putSleep(){
	display.ssd1306_command(SSD1306_DISPLAYOFF);	// Put display to sleep
	therm.sleep();			// Put IR sensor to sleep
	ESP.deepSleep(0);		// Put esp to sleep
}

/*******************************************************************************
	wakeUP(void) should revive the MLX IR sensor, and OLED display 
	from sleep mode. it is assumed that the ESP is already revived 
	from the reset pin.
*******************************************************************************/
void TempSens::wakeUp(int type){
	display.ssd1306_command(SSD1306_DISPLAYON);		// Wakeup display
	therm.wake();			// Wakeup IR sensor
	Init();
}

/*******************************************************************************
*
*******************************************************************************/
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

/*******************************************************************************
*
*******************************************************************************/
float TempSens::getTemp(){
	
	const int Avg = 25;                                         // Number of readings to average
	float OF[Avg];                                             // Array to store readings for Object temp in F

	for(int y = 0; y < Avg; y++){
		OF[y] = therm.object();                          // reads temp values
	}
    
	for(int j = 0; j < Avg-1; j++){
		Temp += OF[j];
	}

	Temp = Temp / Avg;                                // Divide by total number of readings for average
    
	return Temp;
}

/*******************************************************************************
*This function takes in a selected amount of time
*While the timer is less than the selected amount of time
*Keep displaying the current temp 
*******************************************************************************/
void TempSens::liveRead(int time){
	//Creates a varaible that creates a timer in miliseconds 
	timer = millis();
	//While the timer is less than the alotted amount of time display the current temp of the person out to the OLED
	while(timer < time)
	{
		float temparary = therm.object();
		display.setTextSize(1);
		display.setTextColor(WHITE);
		display.setCursor(0, 10);
		display.print(temparary);
		display.display();
		delay(100);
		display.clearDisplay();
	}
		//Displays the final temp
		display.print(temparary);	
}

/*******************************************************************************
*This function uses the public bool sick,
*if it is true it will run the sound for a fever
*if it is false then it will non fever sound
*******************************************************************************/
void TempSens::displaySick(){
	if(Sick == True){//Checks to see if Sick is true 
		soundFever();//Plays the Fever sound function
	}
	else{
		soundOK();//Plays the non fever sound function
	}
}

/*******************************************************************************
*
*******************************************************************************/
void TempSens::initWifi(){
	Serial.begin(115200);                                                         //Initializes data rate in bits/s for microcontroller (esp8266)                            

	WiFi.mode(WIFI_STA);                       
	WiFi.begin (ssid, password);                                                 //Starts wifi connection           

	therm.read();  
}

/*******************************************************************************
*
*******************************************************************************/
void TempSens::initTemp(){
	therm.setUnit(TEMP_F);
	Fever_Temp = 100.4;                                                //Double that holds value for temperature that classifies as too high
}

/*******************************************************************************
*Function that initializes the OLED
*******************************************************************************/
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

/*******************************************************************************
* Function that generates a tone played by the buzzer when the temp is above the fever limit
*******************************************************************************/
void TempSens::soundFever(){
	for(int i = 0; i < 4; i++)
	{
		tone(buzzer, 3000);//Sends a 3KHz sound signal to the buzzer
		delay(500); //wait hald a second
		noTone(buzzer); //Stops the buzzers sound
	}
}

/*******************************************************************************
 * Function that generates a tone played by the buzzer when the temp is below the fever limit
 *******************************************************************************/
void TempSens::soundOK(){
		
	tone(buzzer, 460);//Sends a 460Hz sound signal to the buzzer
	delay(500); //wait hald a second
	noTone(buzzer);//Stops the buzzers sound
	tone(buzzer, 700);//Sends a 700Hz sound signal to the buzzer
	delay(750); //wait hald a second
	noTone(buzzer);//Stops the buzzers sound
	tone(buzzer, 1100);//Sends a 1.1KHz sound signal to the buzzer
	delay(1000); //wait hald a second
	noTone(buzzer);//Stops the buzzers sound
}

/*******************************************************************************
 * Function that creates a welcome message
 *******************************************************************************/
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

/*******************************************************************************
 * Function that displays a set of diresctions for the user
 *******************************************************************************/
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

/*******************************************************************************
 * Function that displays that the users temp will be taken
 *******************************************************************************/
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

/*******************************************************************************
 * Function that calculates if the users temp is too high
 *******************************************************************************/
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

/*******************************************************************************
 * Function that tests the temp sensor
 *******************************************************************************/
void TempSens::testTempSensor(){
	bool test = 1;
	int val = 0;
	initWifi();
	initTemp();
	
	while(test){
		getTemp();
		Serial.print(Temp); Serial.print("*F ");
		Serial.println();
		
		tempCalc();
		sendData();
		val = val + 1;
		
		if(val = 15)
			test = 0;
	}
}

/*******************************************************************************
 * Function that tests the buzzer
 *******************************************************************************/
void TempSens::testBuzer(){
	soundOK();
}

/*******************************************************************************
 * Function that tests the oled
 *******************************************************************************/
void TempSens::testOled(){
	static const unsigned char PROGMEM logo_bmp[] =
	{ 0b00000000, 0b11000000,
	  0b00000001, 0b11000000,
	  0b00000001, 0b11000000,
	  0b00000011, 0b11100000,
	  0b11110011, 0b11100000,
	  0b11111110, 0b11111000,
	  0b01111110, 0b11111111,
	  0b00110011, 0b10011111,
	  0b00011111, 0b11111100,
	  0b00001101, 0b01110000,
	  0b00011011, 0b10100000,
	  0b00111111, 0b11100000,
	  0b00111111, 0b11110000,
	  0b01111100, 0b11110000,
	  0b01110000, 0b01110000,
	  0b00000000, 0b00110000 };
	uint8_t w = 16;
	uint8_t h = 16;
	int8_t f, icons[NUMFLAKES][3];

	// Initialize 'snowflake' positions
	for(f=0; f< NUMFLAKES; f++) {
		icons[f][XPOS]   = random(1 - w, display.width());
		icons[f][YPOS]   = -h;
		icons[f][DELTAY] = random(1, 6);
		Serial.print(F("x: "));
		Serial.print(icons[f][XPOS], DEC);
		Serial.print(F(" y: "));
		Serial.print(icons[f][YPOS], DEC);
		Serial.print(F(" dy: "));
		Serial.println(icons[f][DELTAY], DEC);
	}

  	for(;;) { // Loop forever...
    		display.clearDisplay(); // Clear the display buffer

		// Draw each snowflake:
		for(f=0; f< NUMFLAKES; f++) {
			display.drawBitmap(icons[f][XPOS], icons[f][YPOS], bitmap, w, h, SSD1306_WHITE);
    		}

		display.display(); // Show the display buffer on the screen
		delay(200);        // Pause for 1/10 second

		// Then update coordinates of each flake...
		for(f=0; f< NUMFLAKES; f++) {
			icons[f][YPOS] += icons[f][DELTAY];
			// If snowflake is off the bottom of the screen...
			if (icons[f][YPOS] >= display.height()) {
				// Reinitialize to a random position, just off the top
				icons[f][XPOS]   = random(1 - w, display.width());
				icons[f][YPOS]   = -h;
				icons[f][DELTAY] = random(1, 6);
			}	
		}
	}
}
