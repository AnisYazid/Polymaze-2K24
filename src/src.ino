#include "algo.h"
#include "buzzer.h"
#include "motors.h"
#include "oled.h"
#include "pid.h"
#include "qtr.h"
#include "tcs.h"

enum directionCheck { go_left, go_right }; // left == 0, right == 1

const int TURNING_SPEED = 150; // speed that it turns with
const int TURNING_TIME = 1500; // time to turn
const int UTURN_TIME = 3000;   // time to uturn
const bool UTURN_DIR = go_right;
const int DEADEND_TIME = 1000; // time to uturn at dead end
const int MOTOR_SPEED1 = 150;
const int MOTOR_SPEED2 = 150;

const bool WALL_FOLLOWING_DIR = go_right;

bool discovered = false;
bool ready = false;

char path[100];
int pathLength = 0;

IRState irState = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
bool btnUp = false;
bool btnDown = false;
bool btnOk = false;

void setup() {
  // motor setup
  pinMode(motor1, OUTPUT);
  pinMode(motor2, OUTPUT);
  pinMode(motor3, OUTPUT);
  pinMode(motor4, OUTPUT);
  pinMode(motor1Speed, OUTPUT);
  pinMode(motor2Speed, OUTPUT);
  // qtr setup
  // for (int i = 0; i < SensorCount; i++) {
  // pinMode(irSensorPins[i], INPUT);
  //}
  setupQTR();
  // extra ir sensors
  pinMode(irRightPin, INPUT_PULLUP);
  pinMode(irLeftPin, INPUT_PULLUP);
  pinMode(irFrontPin, INPUT_PULLUP);
  // tcs setup
  setupTCS();
  // buzzer setup
  pinMode(buzzerPin, OUTPUT);
  // button setup
  pinMode(okButton, INPUT);
  pinMode(upButton, INPUT);
  pinMode(downButton, INPUT);

  // start calibration
  buzzer();
  for (uint16_t i = 0; i < 400; i++) {
    qtr.calibrate();
  }
  Serial.print("finished cal");

  // indicate the beginning of the end
  buzzer(2);

  // setup oled
  setupOLED();
}

void loop() {
  // lineFollow();
  // wallFollow();
  smartTurn();
  oledPrintBars();
  // readButtons();
  // oledMenu(btnUp, btnDown, btnOk);
  // btnUp = false;
  // btnDown = false;
  // btnOk = false;
}

void readButtons() {
  if (digitalRead(okButton) == HIGH) {
    buzzer();
    btnOk = true;
  }
  if (digitalRead(upButton) == HIGH) {
    buzzer();
    btnUp = true;
  }
  if (digitalRead(downButton) == HIGH) {
    buzzer();
    btnDown = true;
  }
}

void turnRight() {
  right(TURNING_SPEED, TURNING_SPEED);
  delay(TURNING_TIME);
}

void turnLeft() {
  left(TURNING_SPEED, TURNING_SPEED);
  delay(TURNING_TIME);
}

void uTurn(bool direction = UTURN_DIR) {
  if (direction == go_right) {
    right(TURNING_SPEED, TURNING_SPEED);
  } else { // go left
    left(TURNING_SPEED, TURNING_SPEED);
  }
  delay(UTURN_TIME);
}

char wallFollow() {
  // this should be enough for line following
  irScan();
  irState = detectPostion();
  char turn = 'F'; // default direction

  if (!irState.irNothing && !irState.irEnd &&
      !irState.irDeadEnd) { // checks for line existance and not the end
    if (!(irState.irRight || irState.irLeft)) { // no intersections
      pidControl(position);                     // calculate correction speed
      setMotors(motorspeeda, motorspeedb);      // apply correction speed
      // forward(MOTOR_SPEED1,MOTOR_SPEED2);
    }

    // follow right wall or left wall
    else {                      // intersection or turn
      if (WALL_FOLLOWING_DIR) { // follow right wall
        if (irState.irRight) {  // turn right if there is a right turn
          turnRight();
          turn = 'R';
        } else if (irState.irFront) {          // follow the line
          pidControl(position);                // calculate correction speed
          setMotors(motorspeeda, motorspeedb); // apply correction speed
          turn = 'S';
        } else if (irState.irLeft) { // there is only left turn
          turnLeft();
          turn = 'L';
        }

      } else {                // follow left wall
        if (irState.irLeft) { // turn left if there is a left turn
          turnLeft();
          turn = 'L';
        } else if (irState.irFront) {          // follow the line
          pidControl(position);                // calculate correction speed
          setMotors(motorspeeda, motorspeedb); // apply correction speed
          turn = 'S';
        } else if (irState.irRight) { // there is only right turn
          turnRight();
          turn = 'R';
        }
      }
    }
  } else if (irState.irDeadEnd) {
    setMotors(TURNING_SPEED, -TURNING_SPEED);
    delay(DEADEND_TIME);
    turn = 'B';
  } else if (irState.irEnd) { // end of the maze
    forward(0, 0);
    buzzer();
    turn = 'E';
  } else { // worst case scenario when it doesn't find a line
    // left(TURNING_SPEED, TURNING_SPEED); // rotate till death
    buzzer();
    forward(0, 0); // stop
  }
  return turn; // the direction it turned
}

void lineFollow() {
  irScan();
  irState = detectPostion();

  if (irState.irNothing) {
    buzzer();
    forward(0, 0);
  } else {
    pidControl(position);
    setMotors(motorspeeda, motorspeedb); // apply correction speed
  }
}

void smartTurn() {
  char turn;

  if (!ready) { // wait for the button to be pressed
    if (digitalRead(okButton) == HIGH) {
      ready = true;
    }
  } else if (!discovered && ready) { // discovering the maze
    irScan();
    irState = detectPostion();
    turn =
        wallFollow(); // turn accordingly and return the direction if it turned

    if (turn != 'E') { // if it didn't reach the end
      markDirection(turn, path, &pathLength);
    } else { // it reached the end
      discovered = true;
      ready = false;
      forward(0, 0);
      buzzer();
    }
  } else if (discovered && ready) { // solving the maze
    irScan();
    irState = detectPostion();

    if (!irState.irEnd) { // if it didn't reach the end
      followDirection(turn);
    } else { // it reached the end
      ready = false;
      forward(0, 0);
      buzzer();
    }
  }
}

void followDirection(char turn) { // placeholder please change
  if (irState.irRight || irState.irLeft || irState.irFront) {
  } else if (turn == 'R') {
    turnRight();
  } else if (turn == 'L') {
    turnLeft();
  } else if (turn == 'B') {
    uTurn();
  }
}
