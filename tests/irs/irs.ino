#include "qtr.h"

void setup() {
	Serial.begin(9600);
	pinMode(irFrontpin, INPUT);
}

void loop() {
	irScan();
	Serial.println(frontReading);
//	delay(900);
}
