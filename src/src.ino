#include "algo.h"
// #include "buzzer.h"
// #include "main2.h"
#include "main2alt.h"
#include "motors.h"
//#include "oled.h"
#include "pid.h"
#include "qtr.h"
// #include "tcs.h"

enum directionCheck { go_left, go_right }; // left == 0, right == 1

const int TURNING_SPEED = 80; // speed that it turns with
//const int TURNING_TIME = 500; // time to turn
const int UTURN_TIME = 1000;   // time to uturn
const bool UTURN_DIR = go_right;
// const int DEADEND_TIME = 1000; // time to uturn at dead end// is uturn time
const int STEP_SPEED = 80; // speed to step forward
const int STEP_TIME = 200;  // time to step forward
// const int MOTOR_SPEED1 = 150;
// const int MOTOR_SPEED2 = 150;

const bool WALL_FOLLOWING_DIR = go_right;

bool discovered = false;
bool ready = false;

char path[100];
int pathLength = 0;

IRState irState = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
// bool btnUp = false;
// bool btnDown = false;
// bool btnOk = false;

void setup() {
  Serial.begin(9600);
  // motor setup
  setupMotors();
  // qtr setup
  setupQTR();
  // buzzer setup
  pinMode(buzzerPin, OUTPUT);

  // button setup
  pinMode(okButton, INPUT_PULLUP);
  pinMode(upButton, INPUT_PULLUP);
  pinMode(downButton, INPUT_PULLUP);
  // led setup
  pinMode(redLedPin, OUTPUT);

  // main2 setup
  setupMain2();

  // start main2 task loop
  startMain2();

  // indicate the beginning of the end
  digitalWrite(buzzerPin, HIGH);
  delay(500);
  digitalWrite(buzzerPin, LOW);
}

void loop() {
  // lineFollow();
  wallFollow();
  // smartTurn();
}

void stepForward() {
  // forward(STEP_SPEED, STEP_SPEED);
  pidControl(position);                // calculate correction speed
  setMotors(motorspeeda, motorspeedb); // apply correction speed
  delay(STEP_TIME);
}
// void stepBackward() {
//   back(STEP_SPEED, STEP_SPEED);
//   delay(STEP_TIME);
// }

void turnRight(bool doStep = true) {
  if (doStep) stepForward();
  right(TURNING_SPEED, TURNING_SPEED);
  delay(50);
  while (digitalRead(irFrontPin) == LOW) {
    right(TURNING_SPEED, TURNING_SPEED);
    delay(50);
  }
  forward(0, 0);
  delay(20);
  // right(TURNING_SPEED, TURNING_SPEED);
  // delay(TURNING_TIME);
}

void turnLeft(bool doStep = true) {
  if (doStep) stepForward();
  left(TURNING_SPEED, TURNING_SPEED);
  delay(50);
  while (digitalRead(irFrontPin) == LOW) {
    left(TURNING_SPEED, TURNING_SPEED);
    delay(50);
  }
  forward(0, 0);
  delay(20);
  // left(TURNING_SPEED, TURNING_SPEED);
  // delay(TURNING_TIME);
}


void uTurn(bool direction = UTURN_DIR) {
  if (direction == go_right) {
    right(TURNING_SPEED, TURNING_SPEED);
  } else { // go left
    left(TURNING_SPEED, TURNING_SPEED);
  }
  delay(UTURN_TIME);
}

void followDirection(char turn, bool doStep = true) { // placeholder please change
  if (irState.irRight || irState.irLeft || irState.irFront) {
  } else if (turn == 'R') {
    turnRight(doStep);
  } else if (turn == 'L') {
    turnLeft(doStep);
  } else if (turn == 'B') {
    uTurn(); // should not be called
  }
}


char wallFollow() {
  irScan();
  irState = detectPostion();

  if (irState.irNothing){
    forward(0, 0); // deadend
    turnRight(false); //u turn
    return 'B';
  }
  else if (irState.irFull){
    stepForward();
    irScan();
    irState = detectPostion();
    if (irState.irFull){
      // end
      forward(0, 0);
      return 'E';
    } else {
      if (WALL_FOLLOWING_DIR ==  go_right) { //right
        turnRight(false); // turn right since it is a T
        return 'R';
      } else{ // left
        turnLeft(false);
        return 'L';
      }
    }
  }
  else if (irState.irMid && (irState.irRight || irState.irLeft)){
    if (irState.irRight && !irState.irLeft){ // right only
      turnRight(false); // turn right since it is a T
      return 'R';
    } else if (irState.irLeft && !irState.irRight){ // left only
      turnLeft(false);
      return 'L';
    } else { // is both
      if (WALL_FOLLOWING_DIR ==  go_right) { //right
        turnRight(false); // turn right since it is a T
        return 'R';
      } else{ // left
        turnLeft(false);
        return 'L';
      }

    }
  }
  else if (irState.irMid && !(irState.irRight || irState.irLeft)){
    pidControl(position);
    setMotors(motorspeeda, motorspeedb);
    return 'F';
  }
}

void lineFollow() {
  irScan();
  irState = detectPostion();

  if (irState.irNothing) {
    // buzzer();
    forward(0, 0);
  } else {
    pidControl(position);
    setMotors(motorspeeda, motorspeedb); // apply correction speed
    Serial.print("speeda: ");
    Serial.println(motorspeeda);
    Serial.print(" speedb: ");
    Serial.println(motorspeedb);
  }
}

int stepCount = 0;
bool hasOptimized = false;
void smartTurn() {
  char turn;

  if (!discovered && !ready) { // wait for the button to be pressed
    if (digitalRead(okButton) == HIGH) {
      ready = true;
      // buzzer();
      delay(500);
    }
  } else if (!discovered && ready) { // discovering the maze
    turn =
        wallFollow(); // turn accordingly and return the direction if it turned

    if (turn != 'E') {                        // if it didn't reach the end
      markDirection(turn, path, &pathLength); // marks and increments
    } else {                                  // it reached the end
      discovered = true;
      ready = false;
      forward(0, 0);
      // buzzer();
    }
  } else if (discovered && !ready) {
    if (!hasOptimized) {
      optimizePath(path, &pathLength, WALL_FOLLOWING_DIR);
      hasOptimized = true;
      // buzzer();
    } else {
      if (digitalRead(okButton) == HIGH) {
        ready = true;
      }
    }

  } else if (discovered && ready) { // solving the maze
    irScan();
    irState = detectPostion();

    if (!irState.irNothing && !irState.irEnd &&
        !irState.irDeadEnd) { // checks for line existance and not the end
      if (!(irState.irRight || irState.irLeft)) { // no intersections
        pidControl(position);                     // calculate correction speed
        setMotors(motorspeeda, motorspeedb);      // apply correction speed
        // forward(MOTOR_SPEED1,MOTOR_SPEED2);
      } else if (stepCount <= pathLength) { // found an intersection
        followDirection(
            path[stepCount]); // turn according to plan, even if wrong!
        stepCount++;
      }
    } else if (irState.irEnd) { // it reached the end or cross
      stepForward();            // confirm which one
      forward(0, 0);
      irScan();
      irState = detectPostion();
      if (!irState.irEnd) { // this is a cross
        // stepBackward();
        followDirection(
            path[stepCount], false); // turn according to plan, even if wrong!
        stepCount++;
        // buzzer();
      } else { // it reached the end
        ready = false;
        forward(0, 0);
        // buzzer();
      }
    } else if (irState.irDeadEnd) {
      // uTurn(UTURN_DIR);
      // something bad
      forward(0, 0);
      // buzzer();
    } else { // worst case scenario when it doesn't find a line
      // left(TURNING_SPEED, TURNING_SPEED); // rotate till death
      // buzzer();
      forward(0, 0); // stop
    }
  }
}

