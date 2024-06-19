// Buzzer pin
const int buzzerPin = ; //adjust pin  

void setupBuzzer() {
    pinMode(buzzerPin, OUTPUT);
}

void buzzer() {
    tone(buzzerPin, 1000); // shoose pin
}