/*
  Program: ESP8266_SERVO_SWEEP_OLED
  Date:    2026-02-19

  Author:  Alejandro Alonso Puig (https://github.com/aalonsopuig) + ChatGPT 5.2
  License: Apache License 2.0

  ---------------------------------------------------------------------------
  Description
  ---------------------------------------------------------------------------
  This program performs a continuous servo sweep from 0° to 180° and back.

  Features:
  - Uses angle-based control (servo.write()).
  - Calculates the equivalent pulse width in microseconds.
  - Displays both angle (degrees) and pulse width (µs) on the OLED.
  - Uses Serial at 74880 baud to align with ESP8266 ROM boot messages.

  Hardware assumptions:
  - NodeMCU ESP8266 v3 with integrated SSD1306 OLED.
  - Servo powered from external 5–6V supply.
  - Common ground between servo supply and ESP8266.
*/

#include <Arduino.h>           // Core Arduino definitions and basic types
#include <Wire.h>              // I2C communication library
#include <Servo.h>             // Servo control (generates PWM pulses)
#include <Adafruit_GFX.h>      // Graphics primitives (text, shapes)
#include <Adafruit_SSD1306.h>  // SSD1306 OLED driver

// ---------------- OLED Configuration ----------------

// OLED resolution
#define SCREEN_WIDTH  128
#define SCREEN_HEIGHT 64

// Typical I2C address for SSD1306
#define OLED_ADDR 0x3C

// Confirmed working I2C pin mapping for this specific board
#define I2C_SDA 14   // GPIO14
#define I2C_SCL 12   // GPIO12

// ---------------- Servo Configuration ----------------

// GPIO used for servo signal (safe, non-boot strap pin)
#define SERVO_PIN 13

// Define pulse range corresponding to 0° and 180°
// These values may be adjusted for specific servos
#define MIN_US 1000
#define MAX_US 2000

// ---------------- Global Objects ----------------

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
Servo servo;

// Current servo angle
int angle = 0;

// Direction of movement: +1 increasing, -1 decreasing
int direction = 1;

// ---------------- Utility Functions ----------------

// Convert angle (0–180°) to microseconds pulse width
int angleToMicroseconds(int angleValue) {
  return map(angleValue, 0, 180, MIN_US, MAX_US);
}

// Draw current angle and pulse width on OLED
void drawData(int angleValue, int pulseUs) {

  display.clearDisplay();                 // Clear display buffer
  display.setTextColor(SSD1306_WHITE);    // Set text color

  display.setTextSize(1);
  display.setCursor(0, 0);
  display.println("Servo sweep test");

  display.setTextSize(2);
  display.setCursor(0, 18);
  display.print("Angle:");                // No space after colon (as requested)
  display.print(angleValue);
  display.print((char)247);               // Degree symbol

  display.setTextSize(1);
  display.setCursor(0, 48);
  display.print("Pulse: ");
  display.print(pulseUs);
  display.print(" us");

  display.display();                      // Transfer buffer to OLED
}

// ---------------- Setup ----------------

void setup() {

  Serial.begin(74880);    // Match ESP8266 ROM boot baud rate
  delay(200);

  // Initialize I2C interface
  Wire.begin(I2C_SDA, I2C_SCL);

  // Initialize OLED display
  if (!display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR)) {
    while (true) delay(1000);  // Halt execution if OLED fails
  }

  // Attach servo and define pulse range
  servo.attach(SERVO_PIN, MIN_US, MAX_US);

  // Initial display update
  drawData(angle, angleToMicroseconds(angle));
}

// ---------------- Main Loop ----------------

void loop() {

  // Calculate equivalent pulse width for current angle
  int pulseUs = angleToMicroseconds(angle);

  // Command servo position
  servo.write(angle);

  // Update OLED display
  drawData(angle, pulseUs);

  // Update angle according to direction
  angle += direction;

  // Reverse direction at limits
  if (angle >= 180) {
    direction = -1;
  }
  else if (angle <= 0) {
    direction = 1;
  }

  delay(15);  // Standard servo refresh interval (~50 Hz)
}
