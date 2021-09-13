#include <Arduino.h>
#include "sensor_readings.h"
#include "settings.h"    // The order is important!

Adafruit_BME280 bme; // No crash when creating object

void setup() {
  pinMode(LED_BUILTIN,OUTPUT);
  Serial.begin(9600);
  bool status;
  status = 1;
  // (you can also pass in a Wire library object like &Wire2)
  status = bme.begin(0x76); // No crash when initializing object
  if (!status) {
    Serial.println("Could not find a valid BME280 sensor, check wiring!");
    while (1);  // Infinite loop
  }
}

void loop() {
  refresh_readings(&bme);  // Passing the bme object to the function as bme is only "global" in this file.
                          // crash when passing object like this "bme".
                          // works when I pass pointer, like this "&bme"
  //refresh_readings();
  delay(2000);
}