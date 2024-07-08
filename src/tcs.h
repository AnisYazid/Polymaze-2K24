// based on the colorview example by adafruit
#include "Adafruit_TCS34725.h"
#include "pins.h"
#include <Wire.h>

Adafruit_TCS34725 tcs = Adafruit_TCS34725();

void setupTCS() {
    if (tcs.begin()) {
        Serial.println("Found color sensor");
    } else {
        Serial.println("No TCS34725 found ");
        while (1);
    }
}


// for sensor input
float red, green, blue;

// color ranges
const float lower_bounds[][3] = {
    {115, 0, 0},  // red
    {0, 60, 115}, // blue
};

const float upper_bounds[][3] = {
    {255, 115, 115}, // red
    {40, 115, 255},  // blue
};

// for outputs
enum Colors { RED,  BLUE, NO_COLOR };
const int NUM_COLORS = Colors::NO_COLOR;
Colors color;

// detects the colors
void detectColor() {
  // reading the colors
  tcs.getRGB(&red, &green, &blue);

  // detecting the color
  int i;
  color = NO_COLOR;
  for (i = 0; i < NUM_COLORS; i++) {
    if (red >= lower_bounds[i][0] && red <= upper_bounds[i][0] &&
        green >= lower_bounds[i][1] && green <= upper_bounds[i][1] &&
        blue >= lower_bounds[i][2] && blue <= upper_bounds[i][2]) {
      color = Colors(i);
    }
  }
}

// output detected color to the rgb led, values should be ok
void colorAction() {
  switch (color) {
  case RED:
      // do something
    break;
  case BLUE:
      // do something
    break;
  default:
      // do something
    break;
  }
}
