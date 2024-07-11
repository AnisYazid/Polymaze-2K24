#include "oled.h"
#include "pins.h"
#include "tcs.h"

bool discovered = false;
bool ready = false;
bool btnUp = false;
bool btnDown = false;
bool btnOk = false;

void readButtons();

void setupMain2() {
  // oled setup
  setupOLED();
  // tcs setup
  setupTCS();
  // red led setup
  pinMode(redLedPin, OUTPUT);
  // button setup
  pinMode(okButton, INPUT_PULLUP);
  pinMode(upButton, INPUT_PULLUP);
  pinMode(downButton, INPUT_PULLUP);
}

void loopMain2(void *parameter) {
  while (true) {
    detectColor();
    readButtons();
    if (!ready && !discovered) {
      oledMenuControl(btnUp, btnDown, btnOk);
    } else if (ready && !discovered) {
      if (color == Colors::NO_COLOR) {
        oledPrintBars();
      } else {
        colorAction();
      }
    } else if (!ready && discovered) {
      oledMenuControl2(btnUp, btnDown, btnOk);
    }

    // reset states
    btnUp = false;
    btnDown = false;
    btnOk = false;
  }
}

void readButtons() {
  if (digitalRead(okButton) == HIGH) {
    buzzer();
    btnOk = true;
  }
  if (digitalRead(upButton) == HIGH) {
    buzzer();
    btnUp = true;
  }
  if (digitalRead(downButton) == HIGH) {
    buzzer();
    btnDown = true;
  }
}

void startMain2() {
  xTaskCreatePinnedToCore(
      loopMain2, "View", 10000, NULL, 1, NULL,
      0); // 0 for core 0, 1 for higher priority, 10000 for stack size
}
