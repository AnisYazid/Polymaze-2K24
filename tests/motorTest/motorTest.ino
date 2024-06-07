#include "motors.h"

void setup() {
	//motor setup
	pinMode(motor1, OUTPUT);
	pinMode(motor2, OUTPUT);
	pinMode(motor1Speed, OUTPUT);
	pinMode(motor2Speed, OUTPUT);
}

void loop() {
	int speed1 = 255;
	int speed2=255;

	forward(speed1,speed2);
	delay(2500);
	right(speed1,speed2);
	delay(2500);
	back(speed1,speed2);
	delay(2500);
	left(speed1,speed2);
	delay(2500);

	//try setMotors if ur done
}
