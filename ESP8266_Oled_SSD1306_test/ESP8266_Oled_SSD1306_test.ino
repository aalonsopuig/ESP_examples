/*
  Program: ESP8266_OLED_BASIC_TEST_74880
  Date:    2026-02-19

  Author:  Alejandro Alonso Puig (https://github.com/aalonsopuig) + ChatGPT 5.2
  License: Apache License 2.0

  ---------------------------------------------------------------------------
  Description
  ---------------------------------------------------------------------------
  Minimal bring-up test for a NodeMCU ESP8266 v3 board with integrated
  0.96" I2C OLED display (SSD1306).

  - Uses Serial at 74880 baud so ESP8266 ROM boot messages are readable.
  - Initializes the OLED via I2C.
  - Displays a confirmation message on screen.
*/

#include <Arduino.h>           // Core Arduino definitions for ESP8266
#include <Wire.h>              // I2C communication library
#include <Adafruit_GFX.h>      // Graphics primitives (text, lines, shapes)
#include <Adafruit_SSD1306.h>  // Driver for SSD1306 OLED displays

// ---- OLED configuration ----
#define SCREEN_WIDTH  128
#define SCREEN_HEIGHT 64
#define OLED_ADDR     0x3C  // Typical I2C address for SSD1306 (try 0x3D if needed)

// ---- I2C pins for this specific board ----
// Confirmed working mapping for this NodeMCU + OLED variant:
#define I2C_SDA 14  // GPIO14
#define I2C_SCL 12  // GPIO12

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

void setup() {

  Serial.begin(74880);      // Use ESP8266 ROM boot baud rate
  delay(200);

  Serial.println();
  Serial.println("Starting ESP8266 OLED basic test...");

  Wire.begin(I2C_SDA, I2C_SCL);  // Initialize I2C with custom pin mapping

  if (!display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR)) {
    Serial.println("ERROR: OLED init failed. Check I2C pins/address.");
    while (true) delay(1000);
  }

  Serial.println("OLED init OK.");

  display.clearDisplay();            // Clear frame buffer
  display.setTextColor(SSD1306_WHITE);

  display.setTextSize(2);            // Large title
  display.setCursor(0, 0);
  display.println("OLED OK");

  display.setTextSize(1);            // Smaller informational text
  display.setCursor(0, 24);
  display.println("ESP8266 bring-up test");

  display.setCursor(0, 40);
  display.println("Serial: 74880 baud");

  display.display();                 // Send buffer to display
}

void loop() {
  // Static test program – no repeated action required.
}
