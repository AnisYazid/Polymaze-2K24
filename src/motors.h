#include "pins.h"

void setupMotors() {
  pinMode(motor1, OUTPUT);
  pinMode(motor2, OUTPUT);
  pinMode(motor3, OUTPUT);
  pinMode(motor4, OUTPUT);
  pinMode(motor1Speed, OUTPUT);
  pinMode(motor2Speed, OUTPUT);
}

void back(int speed1, int speed2) {
  digitalWrite(motor1, 0);
  digitalWrite(motor2, 1);
  digitalWrite(motor3, 0);
  digitalWrite(motor4, 1);
  analogWrite(motor1Speed, speed1);
  analogWrite(motor2Speed, speed2);
}

void forward(int speed1, int speed2) {
  digitalWrite(motor1, 1);
  digitalWrite(motor2, 0);
  digitalWrite(motor3, 1);
  digitalWrite(motor4, 0);
  analogWrite(motor1Speed, speed1);
  analogWrite(motor2Speed, speed2);
}

void right(int speed1, int speed2) {
  digitalWrite(motor1, 1);
  digitalWrite(motor2, 0);
  digitalWrite(motor3, 0);
  digitalWrite(motor4, 1);
  analogWrite(motor1Speed, speed1);
  analogWrite(motor2Speed, speed2);
}

void left(int speed1, int speed2) {
  digitalWrite(motor1, 0);
  digitalWrite(motor2, 1);
  digitalWrite(motor3, 1);
  digitalWrite(motor4, 0);
  analogWrite(motor1Speed, speed1);
  analogWrite(motor2Speed, speed2);
}

// allows bidirectional control from one function
void setMotors(int speed1, int speed2) {
  if (speed1 > 0) { // left
    digitalWrite(motor1, 1);
    digitalWrite(motor2, 0);
  } else {
    digitalWrite(motor1, 0);
    digitalWrite(motor2, 1);
  }
  analogWrite(motor1Speed, abs(speed1));

  if (speed2 > 0) { // right
    digitalWrite(motor3, 1);
    digitalWrite(motor4, 0);
  } else {
    digitalWrite(motor3, 0);
    digitalWrite(motor4, 1);
  }
  analogWrite(motor2Speed, abs(speed2));
}
