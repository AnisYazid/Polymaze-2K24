// based on the colorview example by adafruit
#include "Adafruit_TCS34725.h"
#include "pins.h"
#include <Wire.h>

// for rgb led
//  use ~560  ohm resistor between Red & Blue, ~1K for green (its brighter)

Adafruit_TCS34725 tcs = Adafruit_TCS34725();
// for sensor input
float red, green, blue;

// color ranges
// need changes
const float lower_bounds[][3] = {
    {115, 0, 0},  // red
    {0, 115, 0},  // green
    {0, 60, 115}, // blue

    {0, 115, 115}, // cyan
    {55, 55, 90},  // magenta
    {70, 70, 0}    // yellow
};

const float upper_bounds[][3] = {
    {255, 115, 115}, // red
    {115, 255, 115}, // green
    {40, 115, 255},  // blue

    {115, 255, 255}, // cyan
    {90, 90, 140},   // magenta
    {120, 140, 80}   // yellow
};

// for outputs
enum Colors { RED, GREEN, BLUE, CYAN, MAGENTA, YELLOW, NO_COLOR };
Colors color;

// something to do with converting to something we see better idk
// on another thought isnt this used for live visuals?
byte gammatable[256];
void gammaSetup() {
  for (int i = 0; i < 256; i++) {
    float x = i;
    x /= 255;
    x = pow(x, 2.5);
    x *= 255;
    gammatable[i] = x;
  }
}

// to be in setup code
void ledSetup() {
  ledcAttach(redpin,  12000, 8);
  ledcAttach(greenpin,  12000, 8);
  ledcAttach(bluepin,  12000, 8);
}

// detects the colors
void detectColor() {
  // reading the colors
  tcs.getRGB(&red, &green, &blue);

  // detecting the color
  int i;
  color = NO_COLOR;
  for (i = 0; i < 6; i++) {
    if (red >= lower_bounds[i][0] && red <= upper_bounds[i][0] &&
        green >= lower_bounds[i][1] && green <= upper_bounds[i][1] &&
        blue >= lower_bounds[i][2] && blue <= upper_bounds[i][2]) {
      color = Colors(i);
    }
  }
}

// output detected color to the rgb led, values should be ok
void lightLed() {
  switch (color) {
  case RED:
    red = 255;
    green = 0;
    blue = 0;
    break;
  case GREEN:
    red = 0;
    green = 255;
    blue = 0;
    break;
  case BLUE:
    red = 0;
    green = 0;
    blue = 255;
    break;
  case CYAN:
    red = 0;
    green = 255;
    blue = 255;
    break;
  case MAGENTA:
    red = 255;
    green = 0;
    blue = 255;
    break;
  case YELLOW:
    red = 255;
    green = 255;
    blue = 0;
    break;
  default:
    red = 0;
    green = 0;
    blue = 0;
    break;
  }
  // ngl still not sure bout the gammatable but adafruit say it gud so
  ledcWrite(1, gammatable[(int)red]);
  ledcWrite(2, gammatable[(int)green]);
  ledcWrite(3, gammatable[(int)blue]);
}
