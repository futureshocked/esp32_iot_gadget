#include <Arduino.h>
#include "sensor_readings.h"
#include "TFT_eSPI.h"     // ESP32 Hardware-specific library
#include "settings.h"     // The order is important!


Adafruit_BME280 bme;

TFT_eSPI tft = TFT_eSPI();       // Invoke custom library

uint16_t bg = TFT_BLACK;
uint16_t fg = TFT_WHITE;

void setup() {
  pinMode(LED_BUILTIN,OUTPUT);
  Serial.begin(9600);

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
}

void loop() {
  tft.setCursor(50, 50);
  
  tft.println(millis());
  // refresh_readings(&bme);
  refresh_readings(&bme, &tft);  // Passing the bme object to the function as bme is only "global" in this file.
  delay(2000);
}

