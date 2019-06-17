/*  02.020 - Multi-file program example - main file
 *   sensor.ino

   This file is part of the Arduino IDE version of the project.

   In the course ESP32 Project: Make an IoT Gadget, you will convert
   this Arduiuno IDE project into a PlatformIO project.


   Components
   ----------
    - See https://techexplorations.com/parts/esp32iot/

    IDE
    ---
    Arduino IDE with ESP32 Arduino Code
    (https://github.com/espressif/arduino-esp32)


    Libraries
    ---------
    - FS.h
    - Adafruit_Sensor
    - Adafruit_BME280
    - TFT_eSPI
    - TaskScheduler
    - ezTime
    - EEPROM
    - esp_system

   Connections
   -----------

    - See schematic in lecture 02.07.
    - You can download the schematic from the course resources page.

    Other information
    -----------------
    Use this sketch along side the video lecture 02.020 of ESP32 Project: Make an IOT gadget

    Created on June 10 2019 by Peter Dalmaris

*/

void refresh_readings() {
  float f_temperature;
  float f_humidity;
  float f_pressure;
  float f_altitude;

  digitalWrite(LED_PIN, HIGH);

  f_temperature = bme.readTemperature();
  f_humidity = bme.readHumidity();
  f_pressure = bme.readPressure() / 100.0F;
  f_altitude = bme.readAltitude(SEALEVELPRESSURE_HPA);

  tft.setTextColor(fg, bg);

  tft.loadFont("SansSerif-36"); // Create TTF fonts using instructions at https://pages.uoregon.edu/park/Processing/process5.html

  tft.setRotation(1);

  tft.setCursor(5, 5);
  tft.println("Right now...");
  tft.setTextColor(TFT_YELLOW, bg);

  // Temperature

  tft.fillRect(5, 50, 140, 30, bg);
  tft.setCursor(5, 50);
  tft.print(f_temperature);
  tft.println(" °C");

  // Humidity
  tft.fillRect(5, 90, 130, 30, bg);
  tft.setCursor(5, 90);
  tft.print(f_humidity);
  tft.println(" %");

  // Pressure
  tft.fillRect(5, 130, 200, 30, bg);
  tft.setCursor(5, 130);
  tft.print(f_pressure);
  tft.println(" hPa");

  // Appx altitude
  tft.fillRect(5, 170, 200, 30, bg);
  tft.setCursor(5, 170);
  tft.print(f_altitude);
  tft.println(" m");

    //Send data to Adafruit.IO
    temperature ->save(f_temperature );
    humidity    ->save(f_humidity );
    barpressure ->save(f_pressure );
    altitude    ->save(f_altitude );
   
  
  digitalWrite(LED_PIN, LOW);
  postsCounter();
}
