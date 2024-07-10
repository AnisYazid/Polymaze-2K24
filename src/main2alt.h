#include "oled.h"
#include "pins.h"
#include "tcs.h"

void setupMain2() {
  // oled setup
  setupOLED();
  // tcs setup
  setupTCS();
  // red led setup
  pinMode(redLedPin, OUTPUT);
}

void loopMain2(void *parameter) {
  while (true) {
    detectColor();
    if (color == Colors::NO_COLOR) {
      oledPrintBars();
    } else {
      colorAction();
      delay(1000);
    }
  }
}

void startMain2() {
  xTaskCreatePinnedToCore(
      loopMain2, "View", 10000, NULL, 1, NULL,
      0); // 0 for core 0, 1 for higher priority, 10000 for stack size
}
