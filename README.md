# Team RoboCop
The source code for a line follower and maze solving robot, used for the Polymaze competition by vic-spark-enp.

# Components
The robot utilizes the following modules:
## Controller
- ESP 32 Wroom 32D development board (30 pin)
## Actuators
- 2 x N20 DC motors
- L293D motor driver IC
## Sensors
- Qtr A8 IR array sensor
- TCS34725 color sensor
## Power
- 3 x LiPo 503450 3.7v 1000mAh battery
- 7805 linear voltage regulator IC
## Miscellaneous
- Red Led 
- Buzzer
- SSD1306 OLED screen

# Dependencies
Be sure to have the following libraries installed:
- Wire
- QTRSensors
- Adafruit SSD1306
- Adafruit TCS34725
- Adafruit BusIO
- SPI

# Usage
To use the robot, you'll need to upload the code to the ESP32 WROOM 32D development board using the Arduino IDE. Follow these steps:

1. Connect the ESP32 WROOM 32D development board to your computer using a USB cable.
2. Open the src/src.ino file in the Arduino IDE.
3. In the "Tools" menu, select the appropriate board ("ESP32 Dev Module") and the port.
4. Click the "Upload" button to upload the code to the development board.
5. Once the code is uploaded, disconnect the USB cable and power the robot using the LiPo batteries.
