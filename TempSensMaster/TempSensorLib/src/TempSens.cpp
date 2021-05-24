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

/*
	putSleep(void) should put the OLED display, the MLX IR seonsor,
	and ESP to low-power sleep mode. In this mode the device is 
	expected to only pull 36uA. 
*/
void TempSens::putSleep(){
	display.sleepDisplay();		// Put display to sleep
	mlx.sleep();				// Put IR sensor to sleep
	ESP.deepSleep(0);			// Put esp to sleep
}

/*
	wakeUP(void) should revive the MLX IR sensor, and OLED display 
	from sleep mode. it is assumed that the ESP is already revived 
	from the reset pin.
*/
void TempSens::wakeUp(int type){
	display.wakeDisplay();		// Wakeup display
	mlx.wake();					// Wakeup IR sensor
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

void TempSens::initOLED(){
	
}

void TempSens::soundFever(){
	
}

void TempSens::soundOK(){
	
}