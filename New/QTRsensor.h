#include <QTRSensors.h>

const int motor1 = ; 
const int motor2 = ; 
const int motor1Speed = ; 
const int motor2Speed = ; 
const int leftWallSensorPin = A1;
const int rightWallSensorPin = A2;
QTRSensorsRC qtrrc((unsigned char[]) {2, 3, 4, 5, 6, 7, 8, 9}, 8); // check circuit pins  
unsigned int sensorValues[8];


const int wallThreshold = ; //adjust 


float P = ; //adjust values 
float I = ;
float D = ;
float lastError =;
float integral = ;

void readIRSensors(unsigned int *sensorValues) {
    qtrrc.read(sensorValues);
}

bool isLeftWall() {
    return analogRead(leftWallSensorPin) > 500; // Adjust threshold 
}

bool isRightWall() {
    return analogRead(rightWallSensorPin) > 500; 
}


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
        if (ENDOFMAZE()) {
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

       
        if (ENDOFMAZE()) {
            break;
        }
    }
}

bool ENDOFMAZE() {
   
    return false; 
}
/*void optimizePath() {
    int newpathlength = 0;
    char newpath[100];

    for (int i = 0; i < pathlength; i++) {
        if (i < pathlength - 2 && path[i] == 'L' && path[i + 1] == 'L') {
            newpath[newpathlength++] = 'B'; 
            i++;
        } else if (i < pathlength - 2 && path[i] == 'R' && path[i + 1] == 'R') {
            newpath[newpathlength++] = 'B'; 
            i++;
        } else {
            newpath[newpathlength++] = path[i];
        }
    }
    for (int i = 0; i < newpathlength; i++) {
        path[i] = newpath[i];
    }
    pathlength = newpathlength;
} */


// fastest path 
void followfastestpath() {
    for (int i = 0; i < pathlength; i++) {
        if (path[i] == 'L') {
            leftTurn();
        } else if (path[i] == 'R') {
            rightTurn();
        } else if (path[i] == 'F') {
            forward(200, 200);
        }
    }
}
 





 /* string path="LBLLLBSBLLBSLL"
  input path              output path 
    LBL                          S
     LBS                         R
     RBL                          B
     SBS                           B
     SBL                           R
     LBR                             B
