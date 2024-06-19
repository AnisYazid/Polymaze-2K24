#include <QTRSensors.h>

const int motor1 = ; 
const int motor2 = ; 
const int motor1Speed = ; 
const int motor2Speed = ; 
const int leftWallSensorPin = A1;
const int rightWallSensorPin = A2;
QTRSensorsRC qtrrc((unsigned char[]) {2, 3, 4, 5, 6, 7, 8, 9}, 8); // check  the circuit 
unsigned int sensorValues[8];


const int wallThreshold = ; //adjust 


float Kp = ;
float Ki = ;
float Kd = ;
float lastError =;
float integral = ;

void setup() {
    
    Serial.begin(1);

   
    pinMode(motor1, OUTPUT);
    pinMode(motor2, OUTPUT);
    pinMode(motor1Speed, OUTPUT);
    pinMode(motor2Speed, OUTPUT);

    
    pinMode(leftWallSensorPin, INPUT);
    pinMode(rightWallSensorPin, INPUT);
    qtrrc.calibrate();
}

void loop() {
    
}



//right/left hand rule 
void solveMazeWithLeftHandRule() {
    unsigned int sensorValues[8];
    while (true) {
        readIRSensors(sensorValues);
        pidControl(sensorValues);

        if (!isLeftWall()) {
            leftTurn();
            path[pathLength++] = 'L';
        } else if (!isRightWall()) {
            rightTurn();
            path[pathLength++] = 'R';
        } else {
            forward(200, 200);
            path[pathLength++] = 'F';
        }
        if (isAtEndOfMaze()) {
            break;
        }
    }
}

void solveMazeWithRightHandRule() {
    unsigned int sensorValues[8];
    while (true) {
        readIRSensors(sensorValues);
        pidControl(sensorValues);

        if (!isRightWall()) {
            rightTurn();
            path[pathLength++] = 'R';
        } else if (!isLeftWall()) {
            leftTurn();
            path[pathLength++] = 'L';
        } else {
            forward(200, 200);
            path[pathLength++] = 'F';
        }

       
        if (isAtEndOfMaze()) {
            break;
        }
    }
}

bool isAtEndOfMaze() {
   
    return false; 
}



// fastest path 
void optimizePath() {
    
}

void followFastestPath() {
    for (int i = 0; i < pathLength; i++) {
        if (path[i] == 'L') {
            leftTurn();
        } else if (path[i] == 'R') {
            rightTurn();
        } else if (path[i] == 'F') {
            forward(200, 200);
        }
    }
}


void readIRSensors(unsigned int *sensorValues) {
    qtrrc.read(sensorValues);
}

bool isLeftWall() {
    return analogRead(leftWallSensorPin) > 500; // Adjust threshold 
}

bool isRightWall() {
    return analogRead(rightWallSensorPin) > 500; 
}

