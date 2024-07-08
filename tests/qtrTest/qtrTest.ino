#include "qtr.h"
#include "motors.h"
#include "buzzer.h"

void setup() {
	Serial.begin(9600);
	//qtr setup
	for (int i = 0; i < SensorCount; i++) {
		pinMode(irSensorPins[i], INPUT);
	}
	pinMode(irFrontpin, INPUT);
	
	//motor setup
	pinMode(motor1, OUTPUT);
	pinMode(motor2, OUTPUT);
	pinMode(motor1Speed, OUTPUT);
	pinMode(motor2Speed, OUTPUT);
	forward(0,0);
	pinMode(buzzerPin, OUTPUT);
	buzzer();
}

void loop() {
	int i;
	IRState irstates;
	irScan();
	irstates = detectPostion();
	Serial.print("sensorValues: ");
		for(i=0; i< SensorCount; i++){
			Serial.print(sensorValues[i]);
			Serial.print(", ");
		}
	Serial.println("");
	Serial.print("position: ");
	Serial.println(position);
	Serial.print("readsum: ");
	Serial.println(readsum);
	Serial.print("irFull: ");
	Serial.println(irstates.irFull);
	Serial.print("irRight: ");
	Serial.println(irstates.irRight);
	Serial.print("irLeft: ");
	Serial.println(irstates.irLeft);
	Serial.print("irNothing: ");
	Serial.println(irstates.irNothing);
	Serial.print("irMid: ");
	Serial.println(irstates.irMid);
	Serial.print("irFront: ");
	Serial.println(irstates.irFront);
	Serial.print("irEnd: ");
	Serial.println(irstates.irEnd);
	Serial.print("irDeadEnd: ");
	Serial.println(irstates.irDeadEnd);
	Serial.print("irRightMost: ");
	Serial.println(irstates.irRightMost);
	Serial.print("irLeftMost: ");
	Serial.println(irstates.irLeftMost);
	Serial.println("_________________________");
	delay(800);
}
