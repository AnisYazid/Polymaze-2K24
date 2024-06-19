void forward(int leftSpeed, int rightSpeed) {
    analogWrite(motor1Speed, leftSpeed);
    digitalWrite(motor1, HIGH);
    analogWrite(motor2Speed, rightSpeed);
    digitalWrite(motor2, HIGH);
}

void leftTurn() {
    analogWrite(motor1Speed, 150);
    digitalWrite(motor1, LOW);
    analogWrite(motor2Speed, 150);
    digitalWrite(motor2, HIGH);
    delay(500); // Adjust delay 
}

void rightTurn() {
    analogWrite(motor1Speed, 150);
    digitalWrite(motor1, HIGH);
    analogWrite(motor2Speed, 150);
    digitalWrite(motor2, LOW);
    delay(500); // Adjust delay 
}
void backward(int leftSpeed, int rightSpeed) {
    analogWrite(motor1Speed, leftSpeed);
    digitalWrite(motor1, LOW);
    analogWrite(motor2Speed, rightSpeed);
    digitalWrite(motor2, LOW);
}