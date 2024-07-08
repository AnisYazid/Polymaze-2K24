#include <Adafruit_SSD1306.h>

// OLED display settings
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

void setupOLED() {
  // Initialize the OLED display
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
}

void oledPrintBars() {
  // Clear the display
  display.clearDisplay();
  // Draw the gauge for each sensor
  for (uint8_t i = 0; i < SensorCount; i++) {
    int16_t gaugeHeight = map(sensorValues[i], 0, 1023, 0, SCREEN_HEIGHT - 8);
    display.drawRect(i * 16, SCREEN_HEIGHT - 8, 12, 8, SSD1306_WHITE);
    display.fillRect(i * 16 + 2, SCREEN_HEIGHT - 8 - gaugeHeight, 8,
                     gaugeHeight, SSD1306_WHITE);
  }
  display.display();
}

int currentMenuIndex = 0;
const int menuItems = 3;

String menu[menuItems] = {"Anis", "Delegue", "Foufou"};

void displayMenu() {
  display.clearDisplay();
  for (int i = 0; i < menuItems; i++) {
    if (i == currentMenuIndex) {
      display.setTextColor(SSD1306_BLACK, SSD1306_WHITE);
    } else {
      display.setTextColor(SSD1306_WHITE, SSD1306_BLACK);
    }
    display.setCursor(0, i * 10);
    display.print(menu[i]);
  }
  display.display();
}

void oledMenu(bool buttonup, bool buttondown, bool buttonOk) {
  if (buttonup == LOW) {
    currentMenuIndex--;
    if (currentMenuIndex < 0) {
      currentMenuIndex = menuItems - 1;
    }
    displayMenu();
  }

  if (buttondown == LOW) {
    currentMenuIndex++;
    if (currentMenuIndex >= menuItems) {
      currentMenuIndex = 0;
    }
    displayMenu();
  }

  if (buttonOk == LOW) {
    executeMenuAction(currentMenuIndex);
  }
}

void executeMenuAction(int index) {
  switch (index) {
  case 0:
    Serial.println("Anis");
    break;
  case 1:
    Serial.println("Delegue");
    break;
  case 2:
    Serial.println("Foufou");
    break;
  }
}
