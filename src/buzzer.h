#include <esp32-hal-timer.h>
#include "pins.h"

// needs change
// make sure to know the hardware timer pins

hw_timer_t *buzzerTimer = NULL;

void ARDUINO_ISR_ATTR onTimerISR() {
  noTone(buzzerPin);
  digitalWrite(buzzerPin, LOW); // Turn off the LED
}



void buzzer() {
  tone(buzzerPin, 1000);
  buzzerTimer = timerBegin(1000000); // Use timer wtih 1MHz frequency
  timerAttachInterrupt(buzzerTimer, &onTimerISR); // Attach the callback function
  timerAlarm(buzzerTimer, 1000000, false, 0); // Set the alarm for 1s
  timerStart(buzzerTimer); // Start the alarm
}
