#include "buzzer.h"

void setup() {
	//buzzer setup
	pinMode(buzzerPin, OUTPUT);

	buzzer();
	delay(3000);
	buzzer(3);
}

void loop() {
}
