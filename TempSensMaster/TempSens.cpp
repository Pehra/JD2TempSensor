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
  Serial.begin(115200); // Initialize Serial to log output
  Serial.println();
  Serial.println("Serial started...");
  
  Wire.begin(); //Joing I2C bus

  initTemp();
  initOLED();
  //initWifi();
}

/*******************************************************************************
	putSleep(void) should put the OLED display, the MLX IR seonsor,
	and ESP to low-power sleep mode. In this mode the device is 
	expected to only pull 36uA. 
*******************************************************************************/
void TempSens::putSleep(){
  //Gose into deep sleep mode
  Serial.println("Going to deep sleep");
  
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
  //restart reason
  Serial.println(""); Serial.print("Reason startup :");Serial.println(ESP.getResetReason());
  
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
*loops for timer * .2sec
*Keep displaying the current temp 
*******************************************************************************/
void TempSens::liveRead(unsigned long timer){
	//While the timer is less than the alotted amount of time display the current temp of the person out to the OLED
	for(int i =0; i < timer; i++){
    Serial.println(i);
    display.clearDisplay();
    
		display.setTextSize(2);
		display.setTextColor(WHITE);
		display.setCursor(16, 64);
   
    if (therm.read()){ 
      display.print(therm.object());
      display.display();
    }else{Serial.println("therm.read() failed - in liveRead()");}
		
		delay(200);
	}
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
	WiFi.mode(WIFI_STA);                       
	WiFi.begin (ssid, password);                 //Starts wifi connection    

  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println();

  Serial.print("Connected, IP address: ");
  Serial.println(WiFi.localIP());
}

/*******************************************************************************
*
*******************************************************************************/
void TempSens::initTemp(){
	if (therm.begin() == false){ // Initialize thermal IR sensor
    Serial.println("Qwiic IR thermometer did not acknowledge! Freezing!");
    while(1);
  }
  Serial.println("Qwiic IR Thermometer connected...");
  
  therm.setUnit(TEMP_F); // Set the library's units to Farenheit
  // Alternatively, TEMP_F can be replaced with TEMP_C for Celsius or
  // TEMP_K for Kelvin.
  delay(500); // Pause for 0.5 seconds
}

/*******************************************************************************
*Function that initializes the OLED
*******************************************************************************/
void TempSens::initOLED(){
  display = Adafruit_SSD1306(128, 32, &Wire);
  //Starts up the screen
  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)){
    Serial.println(F("SSD1306 allocation failed"));
    for (;;); // Don't proceed, loop forever
  }
  Serial.println("OLED Connected...");
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
		tone(BuzzerPin, 3000);//Sends a 3KHz sound signal to the buzzer
		delay(500); //wait hald a second
		noTone(BuzzerPin); //Stops the buzzers sound
	}
}

/*******************************************************************************
 * Function that generates a tone played by the buzzer when the temp is below the fever limit
 *******************************************************************************/
void TempSens::soundOK(){
		
	tone(BuzzerPin, 460);//Sends a 460Hz sound signal to the buzzer
	delay(500); //wait hald a second
	noTone(BuzzerPin);//Stops the buzzers sound
	tone(BuzzerPin, 700);//Sends a 700Hz sound signal to the buzzer
	delay(750); //wait hald a second
	noTone(BuzzerPin);//Stops the buzzers sound
	tone(BuzzerPin, 1100);//Sends a 1.1KHz sound signal to the buzzer
	delay(1000); //wait hald a second
	noTone(BuzzerPin);//Stops the buzzers sound
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
void TempSens::Instructions_for_user(){
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
void TempSens::Letting_user_know_temp_is_being_taken(){
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
	
	if(Temp < FeverTemp){  //If statement to determine if the temp is lower than 100.4 degrees farenheit. Defines bool for OLED as false
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
  // Call therm.read() to read object and ambient temperatures from the sensor.
  if (therm.read()){ // On success, read() will return 1, on fail 0.
    // Use the object() and ambient() functions to grab the object and ambient
    // temperatures.
    // They'll be floats, calculated out to the unit you set with setUnit().
    Serial.print("Object: " + String(therm.object(), 2));
    Serial.println("F");
    Serial.print("Ambient: " + String(therm.ambient(), 2));
    Serial.println("F");
    Serial.println();
  }else{Serial.println("therm.read() failed - in testTempSensor()");}
  
  delay(1000);
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
  #define XPOS   0 // Indexes into the 'icons' array in function below
  #define YPOS   1
  #define DELTAY 2
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
  uint8_t NUMFLAKES = 10;
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
			display.drawBitmap(icons[f][XPOS], icons[f][YPOS], logo_bmp, w, h, SSD1306_WHITE);
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
