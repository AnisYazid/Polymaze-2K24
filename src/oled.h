#include <Adafruit_SSD1306.h>

// OLED display settings
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

void setupOLED() {
  // Initialize the OLED display
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
}

void oledPrintBars() {
  // Clear the display
  display.clearDisplay();
  // Draw the gauge for each sensor
  for (uint8_t i = 0; i < SensorCount; i++) {
    int16_t gaugeHeight = map(sensorValues[i], 0, 1023, 0, SCREEN_HEIGHT - 8);
    display.drawRect(i * 16, SCREEN_HEIGHT - 8, 12, 8, SSD1306_WHITE);
    display.fillRect(i * 16 + 2, SCREEN_HEIGHT - 8 - gaugeHeight, 8, gaugeHeight, SSD1306_WHITE);
  }
  display.display();
}
