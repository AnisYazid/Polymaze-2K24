SKETCH = .

# Specify the ESP32 board variant and serial port
BOARD = esp32:esp32:esp32
PORT = /dev/ttyUSB0

# Specify the Arduino CLI command
ARDUINO_CLI = arduino-cli

# Specify the build directory
BUILD_DIR = build

.PHONY: all
all: compile upload

.PHONY: compile
compile:
	@$(ARDUINO_CLI) compile --fqbn $(BOARD) $(SKETCH) --build-path $(BUILD_DIR)

.PHONY: upload
upload:
	@$(ARDUINO_CLI) upload -p $(PORT) --fqbn $(BOARD) $(SKETCH) -i $(BUILD_DIR)

.PHONY: clean
clean:
	@rm -rf $(BUILD_DIR)
