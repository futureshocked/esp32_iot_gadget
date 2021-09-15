#include <Arduino.h>
#include "sensor_readings.h"
#include "TFT_eSPI.h"     // ESP32 Hardware-specific library
#include "settings.h"

Adafruit_BME280 bme; // I2C

TFT_eSPI tft = TFT_eSPI(); 

uint16_t bg = TFT_BLACK;
uint16_t fg = TFT_WHITE;

void setup() {
  // put your setup code here, to run once:
  pinMode(LED_BUILTIN,OUTPUT);
  Serial.begin(9600);

  if (!SPIFFS.begin()) {
    Serial.println("SPIFFS initialisation failed!");
    while (1) yield(); // Stay here twiddling thumbs waiting
  }

  tft.init();

  tft.setRotation(1);
  tft.loadFont("SansSerif-36"); // Create TTF fonts using instructions at https://pages.uoregon.edu/park/Processing/process5.html
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

  tft.loadFont("NotoSansBold15");
  tft.fillScreen(bg); // Clear the screen
}

void loop() {
  // put your main code here, to run repeatedly:
  refresh_readings(&bme, &tft);
  delay(2000);
}
