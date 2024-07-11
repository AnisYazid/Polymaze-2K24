float Kp = 0.6; // related to the proportional control term;
// change the value by trial-and-error (ex: 0.07).
float Ki = 0; // related to the integral control term;
// change the value by trial-and-error (ex: 0.0008).
float Kd = 0.35; // related to the derivative control term;
// change the value by trial-and-error (ex: 0.6).

int P;
int I;
int D;
int lastError = 0;

// Motor speed variables (choose between 0 - no speed, and 255 - maximum speed)
const uint8_t maxspeeda = 255;
const uint8_t maxspeedb = 255;
const uint8_t minspeeda = 55;
const uint8_t minspeedb = 55;
const uint8_t basespeeda = 150;
const uint8_t basespeedb = 150;
int motorspeeda = 0;
int motorspeedb = 0;

// calcs corrected motor speeds
void pidControl(int position) {
  int error = 3500 - position; // 3500 is the ideal position (the center)

  P = error;
  I = I + error;
  D = error - lastError;
  lastError = error;

  int motorspeed = P * Kp + I * Ki + D * Kd; // calculate the correction

  motorspeeda = basespeeda + motorspeed;
  motorspeedb = basespeedb - motorspeed;

  if (motorspeeda > maxspeeda) {
    motorspeeda = maxspeeda;
  }
  if (motorspeedb > maxspeedb) {
    motorspeedb = maxspeedb;
  }
  if (motorspeeda < 0) {
    motorspeeda = minspeeda;
  }
  if (motorspeedb < 0) {
    motorspeedb = minspeedb;
  }
}
