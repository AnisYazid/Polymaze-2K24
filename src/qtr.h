#include "pins.h"


uint16_t sensorValues[SensorCount];
uint16_t avgsensorValues[SensorCount][5];
//uint16_t position;
float position;
uint16_t readsum;
const int leftbound = 2000;//3000;
const int rightbound = 5000;//4000;
const int thres = 3100; //threshhold value, max sensor reading is 4095
bool irFull = false;
bool irRight = false;
bool irLeft = false;
bool irNothing = false;
bool irMid = false;

const int thresFr=1000;
const int irFrontpin = 27;
int frontReading = 0;
bool irFront = false;

void irScan(){
	// Read each sensor 5 times and store the readings in an array
	for (int j = 0; j < 5; j++) {
		for (int i = 0; i < SensorCount; i++) {
	    avgsensorValues[i][j] = analogRead(irSensorPins[i]);
	  }
	}

	// Calculate the average value for each sensor
	for (int i = 0; i < SensorCount; i++) {
	  int sum = 0;
	  for (int j = 0; j < 5; j++) {
	    sum += avgsensorValues[i][j];
	  }
	  sensorValues[i] = sum / 5;
	}

	frontReading = digitalRead(irFrontpin);

	//resets vars
	position=0;
	readsum=0;
	int i;

	// calculating weighted average
	for(i=0; i< SensorCount; i++){
		position+= i*1000*sensorValues[i];
		readsum+= sensorValues[i];
	}

	if( readsum>0) {position = position/readsum;} 
	// value is between 0 and 7000
	// 0 to the right, 1000 for each sensor 
	// 7000 to the left 
}

void detectPostion(){
	irFront= false;
	//front ir check
	if(frontReading>thresFr){
		irFront=true;
	}

	irFull= false, irRight= false, irLeft= false, irNothing= false, irMid= false;
	
	// testing the case of all sensors detecting the line
	if ( sensorValues[1] >= thres && sensorValues[2] >= thres && sensorValues[3] >= thres &&
		sensorValues[4] >= thres && sensorValues[5] >= thres && sensorValues[6] >= thres ) {
		irFull=true;
	}
	else if ((sensorValues[0]>= thres && sensorValues[1]>=thres && sensorValues[2]>=thres ) && (sensorValues[6]<thres && sensorValues[7]<thres )){
		irLeft=true;
	}
	else if ((sensorValues[7]>= thres && sensorValues[6]>=thres && sensorValues[5]>=thres) && (sensorValues[0]<thres && sensorValues[1]<thres )){
		irRight=true;
	}
	else if( (sensorValues[1]>=thres ||sensorValues[2]>=thres ||sensorValues[3]>=thres || sensorValues[4]>=thres || sensorValues[5]>=thres || sensorValues[6]>=thres )){
		irMid=true;
	}
	else{
		irNothing=true;
	}
}
