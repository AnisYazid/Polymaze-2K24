#pragma once
#include "qtr.h"
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

String menu[menuItems] = {"Follow Right Wall", "Follow Left Wall", "Ready!"};

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

void executeMenuAction(int index) {
  switch (index) {
  case 0:
    // direction = right;
    break;
  case 1:
    // direction = left;
    break;
  case 2:
    // ready = true;
    break;
  }
}

void oledMenuControl(bool buttonup, bool buttondown, bool buttonOk) {
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






void displayPrisonBreak() {
  // Draw the text "PRISON BREAK" centered on the display, with alternating
  // colors and flashing
  int16_t x = display.width() / 2;
  int16_t y = display.height() / 2;
  for (int i = 0; i < 4; i++) {
    display.setTextSize(2);
    if (i % 2 == 0) {
      display.setTextColor(SSD1306_WHITE);
    } else {
      display.setTextColor(SSD1306_BLACK, SSD1306_WHITE); // Inverted color
    }
    display.setCursor(x - (12 * 8) / 2,
                      y - 8 / 2); // Adjust the x and y positions as needed
    display.println("PRISON BREAK");
    display.display();
    delay(200); // Pause for 0.5 seconds
    display.clearDisplay();
    display.display();
    delay(200); // Pause for 0.5 seconds
  }
  display.setTextSize(1);
}





int currentMenuIndex2 = 0;
const int menuItems2 = 1;

String menu2[menuItems2] = { "Final Ready!"};

void displayMenu2() {
  display.clearDisplay();
  for (int i = 0; i < menuItems2; i++) {
    if (i == currentMenuIndex2) {
      display.setTextColor(SSD1306_BLACK, SSD1306_WHITE);
    } else {
      display.setTextColor(SSD1306_WHITE, SSD1306_BLACK);
    }
    display.setCursor(0, i * 10);
    display.print(menu2[i]);
  }
  display.display();
}

void executeMenuAction2(int index) {
  switch (index) {
  case 0:
    // direction = right;
    break;
  }
}

void oledMenuControl2(bool buttonup, bool buttondown, bool buttonOk) {
  if (buttonup == LOW) {
    currentMenuIndex2--;
    if (currentMenuIndex2 < 0) {
      currentMenuIndex2 = menuItems2 - 1;
    }
    displayMenu2();
  }

  if (buttondown == LOW) {
    currentMenuIndex2++;
    if (currentMenuIndex2 >= menuItems) {
      currentMenuIndex2 = 0;
    }
    displayMenu2();
  }

  if (buttonOk == LOW) {
    executeMenuAction2(currentMenuIndex2);
  }
}
