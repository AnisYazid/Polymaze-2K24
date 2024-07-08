#include "qtr.h"

void setup() {
	Serial.begin(9600);
	pinMode(irFrontpin, INPUT);
	pinMode(irLeftPin, INPUT);
	pinMode(irRightPin, INPUT);
}

void loop() {
	irScan();
	Serial.println(frontReading);
	Serial.println(leftReading);
	Serial.println(rightReading);
	delay(900);
}
