#include "tcs.h"


void task(void *parameter){
	ledSetup();
	while(1){
		detectColor();
		lightLed();
	}
}

void setup() {
	Serial.begin(9600); 
	//ledSetup();
	gammaSetup();
	//ledSetup();

	if (tcs.begin()) {
	    Serial.println("Found sensor");
	  } else {
	    Serial.println("No TCS34725 found ... check your connections");
	  }

  xTaskCreatePinnedToCore(task, "colorView", 10000, NULL, 1, NULL, 0);
}


void loop() {
	delay(500);
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
