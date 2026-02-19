# ESP_examples

This repository contains small, focused example projects for different ESP-based development boards (ESP8266, ESP32, etc.).

The objective is to provide simple, well-documented bring-up tests and functional demonstrations that can serve as hardware validation tools, educational examples, starting templates for larger projects, and quick proof-of-concept sketches.

All examples are structured with incremental validation in mind, testing one subsystem at a time.

---

## ESP8266_Oled_SSD1306_test

**Target board:** NodeMCU ESP8266 v3 with integrated 0.96" I2C OLED (SSD1306)

This program is a minimal hardware bring-up test for the ESP8266 with an SSD1306 OLED display.

The program:

- Initializes Serial at `74880` baud to match the ESP8266 ROM boot output.
- Initializes the OLED via I2C using the Adafruit SSD1306 library.
- Displays a confirmation message on the screen.
- Prints initialization status messages to the Serial monitor.

**Purpose:**

- Verify the toolchain and flashing process.
- Validate I2C communication and OLED functionality.
- Confirm correct I2C pin mapping for the specific board variant.

The example is intentionally simple and static, focusing purely on display initialization and verification.

---

## ESP8266_Servo_Sweep_Oled

**Target board:** NodeMCU ESP8266 v3 with integrated SSD1306 OLED

This example extends the OLED test by adding servo control.

The program:

- Initializes the OLED display.
- Attaches a servo to a GPIO pin.
- Moves the servo smoothly from 0° to 180° and back continuously.
- Displays the current angle on the OLED in real time.
- Outputs the angle value to the Serial monitor.

**Purpose:**

- Validate PWM signal generation at 3.3V logic level.
- Test servo behavior using an external power supply.
- Verify simultaneous operation of I2C (OLED) and PWM (servo).
- Provide a clean baseline for future closed-loop or distributed control experiments.

---

Future examples may include:

- ADC reading and filtering
- WiFi communication tests
- Multi-servo coordination
- micro-ROS integration
- Power robustness experiments
