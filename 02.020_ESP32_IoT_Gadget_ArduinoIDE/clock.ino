/*  02.020 - Multi-file program example - main file
 *   clock.ino

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


void refresh_clock()
{
  //See documentation for ezTime options: https://github.com/ropg/ezTime
  tft.loadFont("NotoSansBold15");
  tft.setTextColor(TFT_LIGHTGREY, bg);  // See available colors at https://github.com/Bodmer/TFT_eSPI/blob/master/TFT_eSPI.h
  //Clear the date area
  tft.fillRect(220, 50, 135, 70, bg);
  // Day of week, day of month
  tft.setCursor(220, 50);
  tft.print(sydneyTZ.dateTime("l")); // Day of week
  // Month and day of month
  tft.setCursor(220, 65);
  tft.print(sydneyTZ.dateTime("F")); // Month
  tft.print(" ");
  tft.print(sydneyTZ.dateTime("j"));  // Day of month
  // Year
  tft.setCursor(220, 80);
  tft.print(sydneyTZ.dateTime("Y")); // Year
  // Time
  tft.setCursor(220, 95);
  tft.print(sydneyTZ.dateTime("H:i:s")); // Time

  indicators();
}
