/******************************
	This librry is for the hands free temperature sensor project
	
	Authors:
		Kaleb Krieger 
		Andrew Pehrson 
		Quentin Onyemordi
		
******************************/

#include "TempSems.h"

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

void TempSens::initOLED(){
	
}

void TempSens::soundFever(){
	
}

void TempSens::soundOK(){
	
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