/*  02.020 - Multi-file program example - main file
 *   ifttt_control.ino

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

void ledMessage(AdafruitIO_Data *data) {

  DEBUGPRINT("received <- ");
  DEBUGPRINTLN(data->value());

  if (!strcmp(data->value(), "off")) {
    digitalWrite(IFTTT_PIN, LOW);
  }

  if (!strcmp(data->value(), "on")) {
    digitalWrite(IFTTT_PIN, HIGH);
  }

}
