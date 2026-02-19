/*
  Program: ESP8266_Servo_Pot_Oled
  Date:    2026-02-19

  Author:  Alejandro Alonso Puig (https://github.com/aalonsopuig) + ChatGPT 5.2
  License: Apache License 2.0

  ---------------------------------------------------------------------------
  Description
  ---------------------------------------------------------------------------
  Potentiometer-to-servo test for NodeMCU ESP8266 v3 with integrated SSD1306 OLED.

  The program:
  - Reads a potentiometer as a voltage divider between 3.3V and GND (wiper to A0).
  - Maps ADC readings (0..1023) directly to a servo angle (0..180).
  - Commands the servo using angle-based control.
  - Displays ADC value, angle (degrees), and pulse width (µs) on the OLED.
  - Uses Serial at 74880 baud to align with ESP8266 ROM boot output.
*/

#include <Arduino.h>           // Core Arduino definitions
#include <Wire.h>              // I2C communication
#include <Servo.h>             // Servo control
#include <Adafruit_GFX.h>      // Graphics primitives
#include <Adafruit_SSD1306.h>  // SSD1306 OLED driver

// ---------------- OLED Configuration ----------------

#define SCREEN_WIDTH  128
#define SCREEN_HEIGHT 64
#define OLED_ADDR     0x3C

#define I2C_SDA 14   // Confirmed working mapping
#define I2C_SCL 12

// ---------------- Potentiometer ----------------

#define POT_PIN A0   // ESP8266 single ADC input

// ---------------- Servo Configuration ----------------

#define SERVO_PIN 13
#define MIN_US    1000
#define MAX_US    2000

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
Servo servo;

// Convert angle to pulse width (for display/debug)
int angleToMicroseconds(int angleValue) {
  return map(angleValue, 0, 180, MIN_US, MAX_US);
}

void drawData(int adcRaw, int angleValue, int pulseUs) {

  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);

  display.setTextSize(1);
  display.setCursor(0, 0);
  display.println("Pot -> Servo test");

  display.setCursor(0, 16);
  display.print("ADC: ");
  display.println(adcRaw);

  display.setTextSize(2);
  display.setCursor(0, 30);
  display.print("Angle:");
  display.print(angleValue);
  display.print((char)247);

  display.setTextSize(1);
  display.setCursor(0, 54);
  display.print("Pulse: ");
  display.print(pulseUs);
  display.print(" us");

  display.display();
}

void setup() {

  Serial.begin(74880);
  delay(200);

  Wire.begin(I2C_SDA, I2C_SCL);

  if (!display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR)) {
    while (true) delay(1000);
  }

  servo.attach(SERVO_PIN, MIN_US, MAX_US);
}

void loop() {

  // Read raw ADC value (0..1023)
  int adcRaw = analogRead(POT_PIN);

  // Map directly to angle
  int angleValue = map(adcRaw, 0, 1023, 0, 180);

  // Command servo
  servo.write(angleValue);

  // Compute pulse width for display
  int pulseUs = angleToMicroseconds(angleValue);

  // Update OLED
  drawData(adcRaw, angleValue, pulseUs);

  // Serial debug
  Serial.print("ADC=");
  Serial.print(adcRaw);
  Serial.print(" Angle=");
  Serial.print(angleValue);
  Serial.print(" Pulse=");
  Serial.println(pulseUs);

  delay(50);
}
