#include "pins.h"
#include <esp32-hal-timer.h>

// needs change
// make sure to know the hardware timer pins

hw_timer_t *buzzerTimer = NULL;
bool isBuzzerActive = false;

const uint64_t BUZZ_TIME = 1000000;  // 1s in microseconds
const uint16_t BUZZ_FREQ = 1000;     // Hz
const uint32_t TIMER_BASE = 1000000; // 1MHz
bool noRunningBuzzer = true;
uint8_t buzzingTimes = 0;

void ARDUINO_ISR_ATTR onTimerISR() {
  if (isBuzzerActive) {
    noTone(buzzerPin);
    isBuzzerActive = false;
  } else {
    tone(buzzerPin, BUZZ_FREQ);
    isBuzzerActive = true;
  }
  if (buzzingTimes > 0) {
    buzzingTimes--;
  } else {
    noRunningBuzzer = true;
  }
  // or ..
  // Set the buzzer pin to the appropriate state
  // digitalWrite(buzzerPin, isBuzzerActive ? LOW : HIGH);
  // Flip the state of the buzzer
  // isBuzzerActive = !isBuzzerActive;
}

void buzzer(int buzz_times = 1) {
  if(noRunningBuzzer) {
    buzzingTimes = 2 * buzz_times - 1;
    noRunningBuzzer = false;
    buzzerTimer = timerBegin(TIMER_BASE); // Use timer wtih 1MHz frequency
    timerAttachInterrupt(buzzerTimer,
                         &onTimerISR); // Attach the callback function
    if (buzz_times <= 1) {
      timerAlarm(buzzerTimer, BUZZ_TIME, false, 0); // Set the alarm once
    } else {
      timerAlarm(buzzerTimer, BUZZ_TIME, true,
                 2 * buzz_times - 1); // Set the alarm for multiple times
    }
    timerStart(buzzerTimer); // Start the alarm

    tone(buzzerPin, BUZZ_FREQ);
    // digitalWrite(buzzerPin, HIGH);
    isBuzzerActive = true;
  }
}
