/*  02.020 - Multi-file program example - main file
 *   SPIFFS_functions.ino

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


/*====================================================================================
  This sketch supports for the ESP6266 and ESP32 SPIFFS filing system

  Created by Bodmer 15th Jan 2017
  ==================================================================================*/

//====================================================================================
//                 Print a SPIFFS directory list (root directory)
//====================================================================================

void listFiles(void) {
  DEBUGPRINTLN();
  DEBUGPRINTLN("SPIFFS files found:");

#ifdef ESP32
  listDir(SPIFFS, "/", true);
#else
  fs::Dir dir = SPIFFS.openDir("/"); // Root directory
  String  line = "=====================================";

  DEBUGPRINTLN(line);
  DEBUGPRINTLN("  File name               Size");
  DEBUGPRINTLN(line);

  while (dir.next()) {
    String fileName = dir.fileName();
    DEBUGPRINT(fileName);
    int spaces = 25 - fileName.length(); // Tabulate nicely
    if (spaces < 0) spaces = 1;
    while (spaces--) Serial.print(" ");
    fs::File f = dir.openFile("r");
    DEBUGPRINT(f.size()); Serial.println(" bytes");
    yield();
  }

  DEBUGPRINTLN(line);
#endif
  DEBUGPRINTLN();
  delay(1000);
}
//====================================================================================

#ifdef ESP32
void listDir(fs::FS &fs, const char * dirname, uint8_t levels) {
  Serial.printf("Listing directory: %s\n", dirname);

  fs::File root = fs.open(dirname);
  if (!root) {
    DEBUGPRINTLN("Failed to open directory");
    return;
  }
  if (!root.isDirectory()) {
    DEBUGPRINTLN("Not a directory");
    return;
  }

  fs::File file = root.openNextFile();
  while (file) {

    if (file.isDirectory()) {
      DEBUGPRINTLN("DIR : ");
      String fileName = file.name();
      DEBUGPRINT(fileName);
      if (levels) {
        listDir(fs, file.name(), levels - 1);
      }
    } else {
      String fileName = file.name();
      DEBUGPRINT("  " + fileName);
      int spaces = 32 - fileName.length(); // Tabulate nicely
      if (spaces < 1) spaces = 1;
      while (spaces--) Serial.print(" ");
      String fileSize = (String) file.size();
      spaces = 8 - fileSize.length(); // Tabulate nicely
      if (spaces < 1) spaces = 1;
      while (spaces--) Serial.print(" ");
      DEBUGPRINTLN(fileSize + " bytes");
    }

    file = root.openNextFile();
  }
}
#endif
