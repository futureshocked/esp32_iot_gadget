#include <Arduino.h>
#include "sensor_readings.h"

// Passing the tft object by reference
    void refresh_readings(  Adafruit_BME280* bme, 
                            TFT_eSPI* tft,
                            AdafruitIO_Feed* temp,
                            AdafruitIO_Feed* hum,
                            AdafruitIO_Feed* bar,
                            AdafruitIO_Feed* alt) {
  float f_temperature;
  float f_humidity;
  float f_pressure;
  float f_altitude;

  digitalWrite(LED_PIN, HIGH);

  tft->loadFont("SansSerif-36"); // Create TTF fonts using instructions at https://pages.uoregon.edu/park/Processing/process5.html
  tft->setRotation(1);
  // uint16_t bg = TFT_BLACK;
  // uint16_t fg = TFT_WHITE;

  tft->setCursor(5, 5);
  tft->setTextColor(TFT_TEXT, TFT_BACKGROUND);
  tft->println("Right now...");

  f_temperature = bme->readTemperature();
  f_humidity    = bme->readHumidity();
  f_pressure    = bme->readPressure() / 100.0F;
  f_altitude    = bme->readAltitude(SEALEVELPRESSURE_HPA);

  tft->setTextColor(TFT_YELLOW, TFT_BACKGROUND);

  DEBUGPRINTLN("--- Sensor readings ---");
  
  // Temperature
  DEBUGPRINT(f_temperature);
  DEBUGPRINTLN(" °C");
  tft->fillRect(5, 50, 140, 30, TFT_BACKGROUND);
  tft->setCursor(5, 50);
  tft->print(f_temperature);
  tft->println(" °C");

  // Humidity
  DEBUGPRINT(f_humidity);
  DEBUGPRINTLN(" %");
  tft->fillRect(5, 90, 130, 30, TFT_BACKGROUND);
  tft->setCursor(5, 90);
  tft->print(f_humidity);
  tft->println(" %");

  // Pressure 
  DEBUGPRINT(f_pressure);
  DEBUGPRINTLN(" hPa");
  tft->fillRect(5, 130, 200, 30, TFT_BACKGROUND);
  tft->setCursor(5, 130);
  tft->print(f_pressure);
  tft->println(" hPa");

  // Appx altitude
  DEBUGPRINT(f_altitude);
  DEBUGPRINTLN(" m");   
  tft->fillRect(5, 170, 200, 30, TFT_BACKGROUND);
  tft->setCursor(5, 170);
  tft->print(f_altitude);
  tft->println(" m");

  //Send data to Adafruit.IO
  temp    ->save(f_temperature );
  hum     ->save(f_humidity );
  bar     ->save(f_pressure );
  alt     ->save(f_altitude );

  digitalWrite(LED_PIN, LOW);
  
  // Update the postsCounter value in the EEPROM and the TFT
  postsCounter(tft);
  DEBUGPRINTLN("----------------");  
}