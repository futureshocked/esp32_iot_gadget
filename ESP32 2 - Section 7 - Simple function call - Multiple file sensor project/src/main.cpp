#include <Arduino.h>
#include "sensor_readings.h"
#include "settings.h"    // The order is important!

Adafruit_BME280 bme;

void setup() {
  pinMode(LED_BUILTIN,OUTPUT);
  Serial.begin(9600);
  bool status;

  // (you can also pass in a Wire library object like &Wire2)
  status = bme.begin(0x76);
  if (!status) {
    Serial.println("Could not find a valid BME280 sensor, check wiring!");
    while (1);  // Infinite loop
  }
}

void loop() {
  refresh_readings(bme);  // Passing the bme object to the function as bme is only "global" in this file.
  delay(2000);
}