
/********************************************************** 
 This is document that is being used for JD 2 Project
to implement a contactless temperature sensor. The code 
also makes use of a library specifically designed to work 
with the infrared temperature sensor being used for the 
data analysis (MLX90614 Temp Sensor). More specific 
information on the library is cited below,
 **********************************************************/

/*************************************************** 
  This is a library example for the MLX90614 Temp Sensor

  Designed specifically to work with the MLX90614 sensors in the
  adafruit shop
  ----> https://www.adafruit.com/products/1747 3V version
  ----> https://www.adafruit.com/products/1748 5V version

  These sensors use I2C to communicate, 2 pins are required to  
  interface
  Adafruit invests time and resources providing this open source code, 
  please support Adafruit and open-source hardware by purchasing 
  products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries.  
  BSD license, all text above must be included in any redistribution
 ****************************************************/

/*****************************************************
 * Library and Hardware setup
 ****************************************************/
#include <Wire.h>                                                                //Allows the hardware implementation with microcontroller
#include <Adafruit_MLX90614.h>                                                  //Includes Adafruit library designed for the Temp. Sensor (MLX90614)
#include <ESP8266WiFi.h>                                                        //Allows ESP8266 to connect to WiFi
#include <time.h>                                                               //Allows time to be calculated via WiFi
#include <string>

String apiKey = "1Y9IDJKPYM654Z82";                                             // Write API key from ThingSpeak

const char* ssid = "esp8266";                                                   //Wifi SSID
const char* password = "12345678";                                             //Wifi Password

const char* server = "api.thingspeak.com";


WiFiClient client;
Adafruit_MLX90614 mlx = Adafruit_MLX90614();                                   //Shortens function call for temp sensor to "mlx"

bool Temp_Check;                                                               //Boolean value to determine if the temperature is too high

double Fever_Temp = 100.4;                                                      //Double that holds value for temperature that classifies as too high  

double Temp_Val;                                                               //Double to hold calculated temp value

String Time_Date = "";                                                              //String holding time and date



/*****************************************************
 * Initialization
 ****************************************************/

void setup() {

initWifi();

}



/*****************************************************
 * Implementation
 ****************************************************/

 
void loop() {
/***********************************************************
 * Prints Ambient and Object Temp in Fareinheit and Celsius 
 **********************************************************/ 
                                      
  
 getTemp();
 tempCalc();
 sendData();

}





/***********************************************************
 * Function to get the time with time function referenced  
 * from github
 **********************************************************/
String get_time(){
  time_t now;
  time(&now);
  char time_output[30];
  // See http://www.cplusplus.com/reference/ctime/strftime/ for strftime functions
  strftime(time_output, 30, "%a  %d-%m-%y %T", localtime(&now)); 
  return String(time_output); 
}


/***********************************************************
 * Function to calculate if the temperature is too high
 **********************************************************/
void tempCalc(){
  
  if(Temp_Val < Fever_Temp){  //If statement to determine if the temp is lower than 100.4 degrees farenheit. Defines bool for OLED as false
    Temp_Check = false;
    Serial.println("Temperature is acceptable");
  }
  else{                       //Else to determine if temp is higher than 100.4 farenheit. Defines bool for OLED as true
    Temp_Check = true;
    Serial.println("Temperature is too high");
  }
  Serial.println();
  delay(500);

}
  

/***********************************************************
 * Function to calculate the temperature and print to the
 monitor
 **********************************************************/
void getTemp(){

   Temp_Val = mlx.readObjectTempF();
   Time_Date = get_time();
}




/***********************************************************
 * Function to get mode of temperatures calculated
 **********************************************************/
void initWifi(){
  
  Serial.begin(115200);                                                         //Initializes data rate in bits/s for microcontroller (esp8266)                            

  Serial.println();
  Serial.print("Wifi connecting to ");
  Serial.println( ssid );

   WiFi.mode(WIFI_STA);                       
  WiFi.begin (ssid, password);                                               //Starts wifi connection

  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }      
               
  configTime(0, 0, "pool.ntp.org", "time.nist.gov");
  setenv("TZ", "PST8PDT,M3.2.0,M11.1.0", 1);  
 
               
  Serial.println();
  Serial.print("WiFi Connected!");
  Serial.println();

  
  Serial.println("Adafruit MLX90614 test");           
  
  mlx.begin();  

}




/***********************************************************
 * Function to calculate the temperature and print to the
 monitor
 **********************************************************/
void sendData(){

   if (client.connect(server,80))   //   "184.106.153.149" or api.thingspeak.com
 {  
   
   String postStr = apiKey;
   postStr +="&field1=";
   postStr += String(Temp_Val);
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

  
  Serial.print(Temp_Val); Serial.print("*F  Date and Time: "); //Serial.println(Time_Date);

  Serial.println();
 }
    client.stop();
  
    delay(2000);
}
