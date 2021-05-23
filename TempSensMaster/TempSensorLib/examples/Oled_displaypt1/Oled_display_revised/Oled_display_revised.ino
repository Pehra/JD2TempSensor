/************************************************************** 
*This is document that is being used for JD 2 Project
*to implement an OLED screen on a contactless temperature 
*sensor. The code also makes use of a library specifically 
*designed to work with the OLED screen being used for the 
*device. 
***************************************************************/

/****************************************************
*Library and Hardware setup
****************************************************/

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels
 
// On an arduino UNO:       A4(SDA), A5(SCL)
#define OLED_RESET     4 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C //Sets the screen address
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);


/****************************************************
*Initialization
****************************************************/
void setup() {
  Serial.begin(9600);

//Add an area for the motion senor module to activate this 

  //Starts up the screen
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) 
  {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }

  // Show initial display buffer contents on the screen --
  // the library initializes this with an Adafruit splash screen.
  delay(500); // Pause for 0.5 seconds

  //Cleares the display
  display.clearDisplay();
 
}

/****************************************************
*Implementation
****************************************************/
 
void loop() {
  // put your main code here, to run repeatedly:

  //Cleares the display from any infromation from last user
  display.clearDisplay();

  //Calls the function that grabs the welcome message
  Welcome_Message();

  //Clears the display of what is currently on it 
  display.clearDisplay();

  //Calls the function that displats the instructions
  Instructions_for_user();

  //clears display
  display.clearDisplay();

  //Calls the functions that lets the user know their temp is going to be taken
  Letting_user_know_temp_is_being_taken();

  //clears display
  display.clearDisplay();

  

  //Incorperate the IR sensor module ot accept a return value and create a command that takes the resulting data and depending on the temp going into differnet branches
}

/****************************************************
*Functions
****************************************************/ 

/***********************************************************
 * Function that creates a welcome message 
 **********************************************************/
  void Welcome_Message()
{
 //Creates the inital greeting for the user
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(20,10);
  display.println("Welcome!");
  display.display();
  delay(2000);//Pauses for 2 seconds
}

/***********************************************************
 * Function that displays a set of diresctions for the user
 **********************************************************/
void Instructions_for_user()
{
  //Block this in with the above set to be triggered by the motion module 
  //Creates instreuctions for the user to follow  
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,10);
  display.print("Please ");
  display.print("stand in");
  display.print("front of ");
  display.print("the sensor.");
  display.display();
  delay(4000);
}

/***********************************************************
 * Function that displays that the users temp will be taken
 **********************************************************/
void Letting_user_know_temp_is_being_taken()
{
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,10);
  display.print("Taking ");
  display.print("your");
  display.print("tempature ");
  display.print("now:");
  display.display();
  delay(1000);
}
