#include "tcs.h"

void setup() {
	Wire.begin();
	Serial.begin(9600); 
	// ledcSetup();
	gammaSetup();

	Serial.println("Color Sensor Test");
	if (tcs.begin()) {
	    Serial.println("Found sensor");
	  } else {
	    Serial.println("No TCS34725 found ... check your connections");
	  }

}

float clear;

void loop() {
	//delay(500);
	detectColor();
	Serial.print("rgb: "); // print a message
	Serial.print(red); 
	Serial.print(", ");
	Serial.print(green); 
	Serial.print(", ");
	Serial.print(blue); 
	Serial.println(" ");
	Serial.print(color);
	Serial.println(" ");


	/*
	for (int i=0;i<6;i++){
		Serial.print(red > lower_bounds[i][0] && red < upper_bounds[i][0]);
		Serial.print(green > lower_bounds[i][1] && green < upper_bounds[i][1]);
		Serial.print(blue > lower_bounds[i][2] && blue < upper_bounds[i][2]);
		Serial.println(" ");
	}
		lightLed();
	*/

	/*
	for( int i=0; i<6;i++){
		color= Colors(i);	
		lightLed();
	Serial.print(color);
	Serial.println(" ");
		delay(1000);
	}
		*/
}
