#include <Arduino.h>
#include "sensor_readings.h"
#include "TFT_eSPI.h"         // ESP32 Hardware-specific library
#include "settings.h"         // The order is important!
#include "bmp_functions.h"  


// SPIFFS plugin for the Arduino IDE: https://github.com/me-no-dev/arduino-esp32fs-plugin

// In this version of the program, start using git.
// In the project root, do "git init", "git add .", "git commit -am "First commit"".
// Once this is done, Code will be showing the changed files in the Source Control pane.



Adafruit_BME280 bme;

TFT_eSPI tft = TFT_eSPI();       // Invoke custom library

uint16_t bg = TFT_BLACK;
uint16_t fg = TFT_WHITE;

void setup() {
  pinMode(LED_BUILTIN,OUTPUT);
  Serial.begin(9600);

  if (!SPIFFS.begin()) {
    tft.println("SPIFFS initialisation failed!");
    while (1) yield(); // Stay here twiddling thumbs waiting
  }

  // Setup the TFT
  tft.begin();

  tft.setRotation(1);
  tft.setTextColor(fg, bg);
  
  tft.fillScreen(bg);
  
  tft.setCursor(0, 0);
  tft.println("Hello!");
  tft.println("Starting BME sensor...");
  delay(5000);

  bool status;

  // (you can also pass in a Wire library object like &Wire2)
  status = bme.begin(0x76);
  if (!status) {
    Serial.println("Could not find a valid BME280 sensor, check wiring!");
    while (1);
  }
  tft.fillScreen(bg);
  drawBmp("/te.bmp", 160, 198, &tft);
}

void loop() {  
  refresh_readings(&bme, &tft);  // Passing the bme object to the function as bme is only "global" in this file.
  delay(2000);
}

