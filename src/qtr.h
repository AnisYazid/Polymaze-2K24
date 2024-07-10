#pragma once
#include "pins.h"
#include <QTRSensors.h>

/*
class ESP32QTRSensors : public QTRSensors {
public:
  void setTypeAnalog() {
    _type = QTRType::Analog;
    _maxValue = 4096; // Override the _maxValue to 4096
  }

protected:
  QTRType _type = QTRType::Analog;
  uint16_t _maxValue = 4096;
};
ESP32QTRSensors qtr;
*/

// QTRSensors qtr;

void setupQTR() {
  // qtr.setTypeAnalog();
  // qtr.setSensorPins(irSensorPins, SensorCount);
  for (int i = 0; i < SensorCount; i++) {
    pinMode(irSensorPins[i], INPUT);
  }

  // extra ir sensors
  pinMode(irFrontPin, INPUT);
}

uint16_t sensorValues[SensorCount];
uint16_t avgsensorValues[SensorCount][5];
// uint16_t position;
float position;
float readsum;
const int leftbound = 3100;  // 3000;
const int rightbound = 3800; // 4000;
const int thres = 2800; // threshhold value, max sensor reading is 4095 
int frontReading = 0;

typedef struct {
  bool irFull;
  bool irLeft;
  bool irMid;
  bool irRight;
  bool irNothing;
  bool irFront;
  bool irRightMost;
  bool irLeftMost;
  bool irEnd;
  bool irDeadEnd;
} IRState;

void printIRState(IRState ir_state) {
  Serial.print("irFull: ");
  Serial.println(ir_state.irFull);
  Serial.print("irLeft: ");
  Serial.println(ir_state.irLeft);
  Serial.print("irMid: ");
  Serial.println(ir_state.irMid);
  Serial.print("irRight: ");
  Serial.println(ir_state.irRight);
  Serial.print("irNothing: ");
  Serial.println(ir_state.irNothing);
  Serial.print("irFront: ");
  Serial.println(ir_state.irFront);
  Serial.print("irRightMost: ");
  Serial.println(ir_state.irRightMost);
  Serial.print("irLeftMost: ");
  Serial.println(ir_state.irLeftMost);
  Serial.print("irEnd: ");
  Serial.println(ir_state.irEnd);
  Serial.print("irDeadEnd: ");
  Serial.println(ir_state.irDeadEnd);
}

void irScan() {
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
  // resets vars
  position = 0;
  readsum = 0;
  int i;

  // calculating weighted average
  for (i = 0; i < SensorCount; i++) {
    position += i * 1000 * sensorValues[i];
    readsum += sensorValues[i];
  }

  if (readsum > 0) {
    position = position / readsum;
  }

  frontReading = digitalRead(irFrontPin);

  // position = qtr.readLineBlack(sensorValues);
  // qtr.read(sensorValues);

  // value is between 0 and 7000
  // 0 to the right, 1000 for each sensor
  // 7000 to the left
}

uint16_t sensorState = 0;
IRState detectPostion() {
  sensorState = 0;
  IRState state = {false, false, false, false, false,
                   false, false, false, false, false};

  // Define the bitmasks for the different IR sensor states
  const uint16_t IR_FULL_MASK = 0b01111110;
  const uint16_t IR_LEFT_MASK = 0b10000000;
  const uint16_t IR_MID_MASK = 0b00111100;
  const uint16_t IR_RIGHT_MASK = 0b00000001;
  const uint16_t IR_NOTHING_MASK = 0b00000000; // is inverted, checks for 0s

  // Combine the sensor values into a single var
  for (int i = 0; i < SensorCount; i++) {
    sensorState |= ((sensorValues[i] >= thres) << i);
  }

  // check for qtr states
  if ((sensorState & IR_FULL_MASK) == IR_FULL_MASK) {
    state.irFull = true;
  }
  if ((sensorState & IR_LEFT_MASK) == IR_LEFT_MASK) {
    state.irLeft = true;
  }
  if ((sensorState & IR_RIGHT_MASK) == IR_RIGHT_MASK) {
    state.irRight = true;
  }
  if ((sensorState & IR_MID_MASK)) {
    state.irMid = true;
  }
  if ((!sensorState & !IR_NOTHING_MASK) == !IR_NOTHING_MASK) {
    state.irNothing = true;
  }

  // check for individual sensors
  if (frontReading) {
    state.irFront = true;
  }
  // if (rightReading >= thresSides) {
  //   state.irRightMost = true;
  // }
  // if (leftReading >= thresSides) {
  //   state.irLeftMost = true;
  // }

  // check for extra conditions
  if (state.irFull && state.irFront && state.irLeft && state.irRight) {
    state.irEnd = true;
  } else if (state.irMid && !state.irFront && !state.irLeft && !state.irRight) {
    state.irDeadEnd = true;
  }

  return state;
}

/*
void detectPostion() {
  irFront = false;
  // front ir check
  if (frontReading > thresFr) {
    irFront = true;
  }

  irFull = false, irRight = false, irLeft = false, irNothing = false,
  irMid = false;

  // testing the case of all sensors detecting the line
  if (sensorValues[1] >= thres && sensorValues[2] >= thres &&
      sensorValues[3] >= thres && sensorValues[4] >= thres &&
      sensorValues[5] >= thres && sensorValues[6] >= thres) {
    irFull = true;
  } else if ((sensorValues[0] >= thres && sensorValues[1] >= thres &&
              sensorValues[2] >= thres) &&
             (sensorValues[6] < thres && sensorValues[7] < thres)) {
    irLeft = true;
  } else if ((sensorValues[7] >= thres && sensorValues[6] >= thres &&
              sensorValues[5] >= thres) &&
             (sensorValues[0] < thres && sensorValues[1] < thres)) {
    irRight = true;
  } else if ((sensorValues[1] >= thres || sensorValues[2] >= thres ||
              sensorValues[3] >= thres || sensorValues[4] >= thres ||
              sensorValues[5] >= thres || sensorValues[6] >= thres)) {
    irMid = true;
  } else {
    irNothing = true;
  }
}
*/
