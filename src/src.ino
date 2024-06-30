#include "buzzer.h"
#include "motors.h"
#include "pid.h"
#include "qtr.h"
#include "tcs.h"

const int TURNING_SPEED = 150; // speed that it turns with
const int TURNING_TIME = 1500; // time to turn
const int MOTOR_SPEED1 = 150;
const int MOTOR_SPEED2 = 150;

const int DirectionSwitch = 2; // placeholder for the moment
bool direction;

void setup() {
  // motor setup
  pinMode(motor1, OUTPUT);
  pinMode(motor2, OUTPUT);
  pinMode(motor3, OUTPUT);
  pinMode(motor4, OUTPUT);
  pinMode(motor1Speed, OUTPUT);
  pinMode(motor2Speed, OUTPUT);
  // qtr setup
  for (int i = 0; i < SensorCount; i++) {
    pinMode(irSensorPins[i], INPUT);
  }
  // tcs setup
  gammaSetup();
  ledSetup();
  // buzzer setup
  pinMode(buzzerPin, OUTPUT);
  // indicate the beginning of the end
  buzzer();
}

void loop() {
  // direction = digitalRead(DirectionSwitch); // will change via menu
  // placeholder for the moment

  // while (true){
  //	wallFollow();
  // }

  lineFollow();
}

void wallFollow() {
  // this should be enough for line following
  irScan();
  detectPostion();

  if (!irNothing) {                       // checks for line existance
    if (!(irRight || irLeft || irFull)) { // no intersections
      pidControl(position);
      setMotors(motorspeeda, motorspeedb); // apply correction speed
      // forward(MOTOR_SPEED1,MOTOR_SPEED2);
    }

    // follow right wall or left wall
    else {             // intersection or turn
      if (direction) { // follow right wall
        if (irRight || irFull) {
          right(TURNING_SPEED, TURNING_SPEED);
          delay(TURNING_TIME);
        } else {
          left(TURNING_SPEED, TURNING_SPEED);
          delay(TURNING_TIME);
        }
      } else { // follow left wall
        if (irLeft || irFull) {
          left(TURNING_SPEED, TURNING_SPEED);
          delay(TURNING_TIME);
        } else {
          right(TURNING_SPEED, TURNING_SPEED);
          delay(TURNING_TIME);
        }
      }
    }
  } else { // worst case scenario when it doesn't find a line
    left(TURNING_SPEED, TURNING_SPEED); // rotate till death
  }
}

void lineFollow() {
  irScan();
  detectPostion();

  pidControl(position);
  setMotors(motorspeeda, motorspeedb); // apply correction speed
}
