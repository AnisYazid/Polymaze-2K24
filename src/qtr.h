#pragma once
#include "pins.h"
#include <QTRSensors.h>

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

void setupQTR() {
  qtr.setTypeAnalog();
  qtr.setSensorPins(irSensorPins,
                    SensorCount);
}

uint16_t sensorValues[SensorCount];
uint16_t avgsensorValues[SensorCount][5];
uint16_t position;
// float position;
uint16_t readsum;
const int leftbound = 3100;  // 3000;
const int rightbound = 3800; // 4000;
const int thres = 3000;      // threshhold value, max sensor reading is 4095
const int irFrontpin = 27;
const int thresSides = 2000; // threshold value for extra side sensors
int frontReading = 0;
int rightReading = 0;
int leftReading = 0;

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

void irScan() {
  frontReading = digitalRead(irFrontpin);
  rightReading = analogRead(irRightPin);
  leftReading = analogRead(irLeftPin);

  position = qtr.readLineBlack(sensorValues);

  // value is between 0 and 7000
  // 0 to the right, 1000 for each sensor
  // 7000 to the left
}

IRState detectPostion() {
  IRState state = {false, false, false, false, false,
                   false, false, false, false, false};
  uint16_t sensorState = 0;

  // Define the bitmasks for the different IR sensor states
  const uint16_t IR_FULL_MASK = 0b11111111;
  const uint16_t IR_LEFT_MASK = 0b11000000;
  // const uint16_t IR_MID_MASK     = 0b00011000;
  const uint16_t IR_RIGHT_MASK = 0b00000011;
  const uint16_t IR_NOTHING_MASK = 0b00000000;

  // Combine the sensor values into a single var
  for (int i = 0; i < SensorCount; i++) {
    sensorState |= ((sensorValues[i] >= thres) << i);
  }

  // check for qtr states
  if ((sensorState & IR_FULL_MASK) == IR_FULL_MASK) {
    state.irFull = true;
  } else if ((sensorState & IR_LEFT_MASK) == IR_LEFT_MASK) {
    state.irLeft = true;
    //} else if ((sensorState & IR_MID_MASK) == IR_MID_MASK){
    //  state.irMid = true;
  } else if ((sensorState & !IR_LEFT_MASK) &
             (sensorState &
              !IR_RIGHT_MASK)) { // check for not left and right WIP
    state.irMid = true;
  } else if ((sensorState & IR_RIGHT_MASK) == IR_RIGHT_MASK) {
    state.irRight = true;
  } else if ((sensorState & IR_NOTHING_MASK) == IR_NOTHING_MASK) {
    state.irNothing = true;
  }

  // check for individual sensors
  if (frontReading) {
    state.irFront = true;
  }
  if (rightReading >= thresSides) {
    state.irRightMost = true;
  }
  if (leftReading >= thresSides) {
    state.irLeftMost = true;
  }

  // check for extra conditions
  if (state.irFull && state.irFront && state.irLeft && state.irRight) {
    state.irEnd = true;
  } else if (state.irMid && !state.irFront) {
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
