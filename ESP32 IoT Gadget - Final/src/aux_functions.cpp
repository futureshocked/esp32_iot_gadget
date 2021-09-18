#include "aux_functions.h"

int postCounter = 0; // Use this counter to indicate (on the TFT screen) how many
                     // MQTT posts where completed in the current power cycle


void wifiStatus(  TFT_eSPI* tft, 
                  AdafruitIO_WiFi* io)
{
  // Wifi status
  tft -> loadFont("NotoSansBold15");
  tft -> setTextColor(TFT_LIGHTGREY, TFT_BLACK);
  tft -> fillRect(5, 220, 150, 20, TFT_BLACK);
  tft -> setCursor(5, 220);
  tft -> print(wl_status_to_string(WiFi.status()));
  //tft -> print(io -> networkStatus());
}

const char* wl_status_to_string(wl_status_t status) {
  switch (status) {
    case WL_NO_SHIELD: return "WL_NO_SHIELD";
    case WL_IDLE_STATUS: return "WL_IDLE_STATUS";
    case WL_NO_SSID_AVAIL: return "WL_NO_SSID_AVAIL";
    case WL_SCAN_COMPLETED: return "WL_SCAN_COMPLETED";
    case WL_CONNECTED: return "Connected";
    case WL_CONNECT_FAILED: return "Connection failed";
    case WL_CONNECTION_LOST: return "WL_CONNECTION_LOST";
    case WL_DISCONNECTED: return "Disconnected";
  }
}

void indicators(  TFT_eSPI* tft, 
                  AdafruitIO_WiFi* io)
{
  wifiStatus(tft, io);
  heapSize(tft);

}

void postsCounter(  TFT_eSPI* tft)
{
  EEPROM.begin(EEPROM_SIZE);
  unsigned int maxPosts = EEPROM.readUInt(EEPROM_INDEX);

  tft->fillRect(200, 0, 10, 10, TFT_GREEN);

  postCounter++; // increment the postCounter by one.
  delay(100);
  if (postCounter > maxPosts)
  {
    tft->fillRect(200, 0, 10, 10, TFT_GREENYELLOW);
    Serial.print("maxPosts:");
    Serial.println(maxPosts);
    maxPosts = postCounter;
    EEPROM.writeUInt(EEPROM_INDEX, maxPosts); // Write the new maxPosts in the EEPROM
    EEPROM.commit();
    delay(500);
  }

  tft->fillRect(200, 0, 10, 10, TFT_BLACK);

  tft->loadFont("NotoSansBold15");
  tft->setTextColor(TFT_LIGHTGREY, TFT_BLACK);
  tft->fillRect(220, 0, 90, 20, TFT_BLACK);
  tft->setCursor(220, 0);
  tft->print(postCounter);
  tft->print("/");
  tft->print(EEPROM.readInt(0));
}

void calibrate_touch_screen(TFT_eSPI* tft)
{
  uint16_t calibrationData[5];
  uint8_t calDataOK = 0;

  DEBUGPRINTLN("starting touch calibration");

  // tft->init();

  tft->setRotation(1); // instead of three
  tft->fillScreen((0xFFFF));

  tft->setCursor(20, 0, 2);
  tft->setTextColor(TFT_BLACK, TFT_WHITE);  tft->setTextSize(1);
  tft->println("calibration run");

  // check file system
  if (!SPIFFS.begin()) {
    DEBUGPRINTLN("formating file system");

    SPIFFS.format();
    SPIFFS.begin();
  }

  // check if calibration file exists
  if (SPIFFS.exists(CALIBRATION_FILE)) {
    fs::File f = SPIFFS.open(CALIBRATION_FILE, "r");    // Using the fs namespace with :: because class File is inside the fs namespace. See FS.h
    if (f) {
      if (f.readBytes((char *)calibrationData, 14) == 14)
        calDataOK = 1;
      f.close();
    }
  }
  if (calDataOK) {
    // calibration data valid
    tft->setTouch(calibrationData);  // To be able to use this function, you must set and uncomment the #define TOUCH_CS 5 in User_Setup.h in TFT_eSPI library
                                     // In PlatformIO, this is stored in .piolibdeps.
  } else {
    // data not valid. recalibrate
    tft->calibrateTouch(calibrationData, TFT_WHITE, TFT_RED, 15);
    // store data
    fs::File f = SPIFFS.open(CALIBRATION_FILE, "w");
    if (f) {
      f.write((const unsigned char *)calibrationData, 14);
      f.close();
    }
  }

  tft->fillScreen((0xFFFF));
}

void readTouch(TFT_eSPI* tft)
{
  uint16_t x, y;
  if (tft->getTouch(&x, &y)) {
    if (x < 3000 && y < 16000)
    {
      tft->fillRect(250, 170, 70, 40, TFT_BLACK);
      tft->setCursor(250, 170, 2);
      tft->printf("x: %i     ", x);
      tft->setCursor(250, 185, 2);
      tft->printf("y: %i    ", y);

      //    tft.drawPixel(320-x, 240-y, TFT_YELLOW);// must adjust the touch coordinates to display coordinates

      if ((x > 40 && x < 90) && ( y > 40 && y < 70))
        digitalWrite(IFTTT_PIN, HIGH);
      else
        digitalWrite(IFTTT_PIN, LOW);
    }
  }
}

void heapSize(TFT_eSPI* tft)
{
  tft->loadFont("NotoSansBold15");
  tft->setTextColor(TFT_LIGHTGREY, TFT_BACKGROUND);
  // Print memory in an attempt to figure out why wifi is unreliable
  tft->fillRect(230, 150, 55, 20, TFT_BACKGROUND);
  tft->setCursor(230, 150);
  tft->print(esp_get_free_heap_size());

  DEBUGPRINT("---- Free heap size: ");
  DEBUGPRINTLN(esp_get_free_heap_size());
}