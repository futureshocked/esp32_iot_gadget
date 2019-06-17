/*  02.020 - Multi-file program example - main file
 *   aux_functions.ino

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


void indicators()
{
  digitalWrite(LED_PIN, HIGH);
  heapSize();
  wifiStatus();
  digitalWrite(LED_PIN, LOW);
  //  postsCounter();
}

void heapSize()
{
  tft.loadFont("NotoSansBold15");
  tft.setTextColor(TFT_LIGHTGREY, bg);
  // Print memory in an attemp to figure out why wifi is unreliable
  tft.fillRect(220, 140, 55, 20, bg);
  tft.setCursor(220, 140);
  tft.print(esp_get_free_heap_size());

  DEBUGPRINT("Free heap size: ");
  DEBUGPRINTLN(esp_get_free_heap_size());
}

void postsCounter()
{
  postCounter++; // New post, increase the post counter
  
  int maxPosts = EEPROM.readInt(0);
  if (postCounter > maxPosts)
  {
    maxPosts = postCounter;
    EEPROM.writeInt(0, maxPosts); // Write the new maxPosts in the EEPROM
    EEPROM.commit();
  }

  tft.loadFont("NotoSansBold15");
  tft.setTextColor(TFT_LIGHTGREY, bg);
  tft.fillRect(220, 0, 90, 20, bg);
  tft.setCursor(220, 0);
  tft.print(postCounter);
  tft.print("/");
  tft.print(EEPROM.readInt(0));
}

void start_wifi()
{
  while (WiFi.status() != WL_CONNECTED) {
    wifiStatus();
    DEBUGPRINT(".");
    // wait 1 second for re-trying
    delay(1000);
    postCounter = 0;  // reset the counter
    wifiStatus();
  }
}

void wifiStatus()
{
  // Wifi status
  tft.loadFont("NotoSansBold15");
  tft.setTextColor(TFT_LIGHTGREY, bg);
  tft.fillRect(5, 220, 150, 20, bg);
  tft.setCursor(5, 220);
  tft.print(wl_status_to_string(WiFi.status()));
  //  tft.print(io.networkStatus());
}

void calibrate_touch_screen()
{
  uint16_t calibrationData[5];
  uint8_t calDataOK = 0;

  DEBUGPRINTLN("starting touch calibration");

  tft.init();

  tft.setRotation(3);
  tft.fillScreen((0xFFFF));

  tft.setCursor(20, 0, 2);
  tft.setTextColor(TFT_BLACK, TFT_WHITE);  tft.setTextSize(1);
  tft.println("calibration run");

  // check file system
  if (!SPIFFS.begin()) {
    DEBUGPRINTLN("formating file system");

    SPIFFS.format();
    SPIFFS.begin();
  }

  // check if calibration file exists
  if (SPIFFS.exists(CALIBRATION_FILE)) {
    File f = SPIFFS.open(CALIBRATION_FILE, "r");
    if (f) {
      if (f.readBytes((char *)calibrationData, 14) == 14)
        calDataOK = 1;
      f.close();
    }
  }
  if (calDataOK) {
    // calibration data valid
    tft.setTouch(calibrationData);
  } else {
    // data not valid. recalibrate
    tft.calibrateTouch(calibrationData, TFT_WHITE, TFT_RED, 15);
    // store data
    File f = SPIFFS.open(CALIBRATION_FILE, "w");
    if (f) {
      f.write((const unsigned char *)calibrationData, 14);
      f.close();
    }
  }

  tft.fillScreen((0xFFFF));
}

void readTouch()
{
  uint16_t x, y;
  if (tft.getTouch(&x, &y)) {
    if (x < 3000 && y < 16000)
    {
      tft.fillRect(220, 160, 70, 40, bg);
      tft.setCursor(220, 160, 2);
      tft.printf("x: %i     ", x);
      tft.setCursor(220, 175, 2);
      tft.printf("y: %i    ", y);

      //    tft.drawPixel(320-x, 240-y, TFT_YELLOW);// must adjust the touch coordinates to display coordinates

      if ((x > 40 && x < 90) && ( y > 40 && y < 70))
        digitalWrite(IFTTT_PIN, HIGH);
      else
        digitalWrite(IFTTT_PIN, LOW);
    }
  }
}
