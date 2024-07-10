#include "tcs.h"

void setup() {
	Wire.begin();
	Serial.begin(9600); 

	Serial.println("Color Sensor Test");
	if (tcs.begin()) {
	    Serial.println("Found sensor");
	  } else {
	    Serial.println("No TCS34725 found ... check your connections");
	  }

}

void loop() {
	delay(200);
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
}
