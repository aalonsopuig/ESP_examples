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

This example performs a continuous servo sweep using angle-based control while displaying both the logical angle and the equivalent pulse width in microseconds.

The program:

- Initializes the SSD1306 OLED display over I2C.
- Attaches a servo to a GPIO pin using a defined pulse range.
- Moves the servo smoothly from 0° to 180° and back continuously.
- Displays the current angle (degrees) on the OLED.
- Displays the corresponding pulse width (µs) derived from the configured minimum and maximum pulse values.
- Uses Serial at 74880 baud to align with the ESP8266 boot output.

**Purpose:**

- Validate PWM signal generation at 3.3V logic level.
- Correlate logical angle commands with actual pulse width values.
- Analyze real mechanical travel versus theoretical 0–180° range.
- Verify stable coexistence of I2C (OLED) and PWM (servo) peripherals.
- Provide a structured baseline for future experiments such as calibrated limits, closed-loop control, or distributed robotic actuation.

---

## ESP8266_Servo_Pot_Oled

**Target board:** NodeMCU ESP8266 v3 with integrated SSD1306 OLED

This example implements direct potentiometer-based control of a servo.

The program:

- Reads a potentiometer connected as a voltage divider between 3.3V and GND (wiper to A0).
- Maps the ADC reading (0–1023) directly to a servo angle (0–180 degrees).
- Commands the servo using angle-based control.
- Displays on the OLED:
  - Raw ADC value
  - Current servo angle (degrees)
  - Equivalent pulse width (microseconds)
- Uses Serial at 74880 baud to align with the ESP8266 boot output.

The OLED layout is arranged so that dynamic measurement data appears in the blue section of bicolor SSD1306 displays, avoiding overlap with the yellow top band.

**Purpose:**

- Validate analog input acquisition on the ESP8266.
- Correlate ADC readings with servo movement.
- Observe real-time response without digital filtering.
- Provide a simple open-loop human interface for servo positioning.
- Serve as a baseline for future experiments involving filtering, calibration, or closed-loop control.

---

Future examples may include:

- ADC reading and filtering
- WiFi communication tests
- Multi-servo coordination
- micro-ROS integration
- Power robustness experiments
