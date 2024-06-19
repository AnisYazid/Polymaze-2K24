#include <Adafruit_TCS34725.h>

// Color sensor
Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_700MS, TCS34725_GAIN_1X);

void setupColorSensor() {
    if (tcs.begin()) {
        Serial.println("Found color sensor");
    } else {
        Serial.println("No TCS34725 found ");
        while (1);
    }
}

void checkForMinigames() {
    uint16_t r, g, b, c;
    tcs.getRawData(&r, &g, &b, &c);

 
    if (r < 100 && g < 100 && b > 150) {
        tone(buzzerPin, 1000, 200); // Emit beep
    }

    
    if (r > 150 && g < 100 && b < 100) {
        digitalWrite(ledPin, HIGH); // Activate LED
    } else {
        digitalWrite(ledPin, LOW);
    }

    // Check for exit point
    if (Exitpoint()) {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Prison Break");
    }
}

bool Exitpoint() {
    // determine the exit point
    return false; 
}