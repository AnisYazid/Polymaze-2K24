#pragma once

#define buzzerPin 23

#define motor1 14      // right wheel
#define motor2 15      // right wheel rev
#define motor3 4       // left wheel
#define motor4 13      // left wheel rev
#define motor1Speed 12 // right wheel speed
#define motor2Speed 18 // left wheel speed

#define okButton 27
#define upButton 99
#define downButton 5

#define irFrontPin 19 // digital
#define irLeftPin 2   // analog
#define irRightPin 27 // analog

#define redLedPin 2

#define SensorCount 8
const uint8_t irSensorPins[SensorCount] = {26, 25, 36, 39, 34, 35, 32, 33};
