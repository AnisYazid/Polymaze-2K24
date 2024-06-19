#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// LCD display
LiquidCrystal_I2C lcd(0x27, 16, 2); // Adjust the I2C address as needed

void setupLCD() {
    lcd.begin();
    lcd.backlight();
}