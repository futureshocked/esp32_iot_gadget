/*  02.020 - Multi-file program example - main file
 *   ESP32_IoT_Gadget_ArduinoIDE

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


// Using code from example sketch Unicode_test from TFT_eSPI library

//#define DEBUGLOG true

#ifdef DEBUGLOG
#define DEBUGPRINT(x)       Serial.print (x)
#define DEBUGPRINTDEC(x)    Serial.print (x, DEC)
#define DEBUGPRINTLN(x)     Serial.println (x)
#else
#define DEBUGPRINT(x)
#define DEBUGPRINTDEC(x)
#define DEBUGPRINTLN(x)
#endif

#include "FS.h" // For handling files
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
// Set "#define TOUCH_CS 5" in  Arduino > libraries > TFT_eSPI > User_Setup.h for the touch interface
#include <TFT_eSPI.h> // Hardware-specific library
#include <TaskScheduler.h>
#include <ezTime.h>
#include "feed_config.h"
#include <EEPROM.h>
#include "esp_system.h"  // To implement the watchdog

#define EEPROM_SIZE 2  // We'll use 2 bytes in the EEPROM to store the max number of POSTs

//TFT calibration
#define CALIBRATION_FILE "/tft-touch-calData"

hw_timer_t *timer = NULL;
const int wdtTimeout = 30000;  //time in ms to trigger the watchdog

int postCounter = 0; // Use this counter to indicate (on the TFT screen) how may

TFT_eSPI tft = TFT_eSPI();       // Invoke custom library

uint16_t bg = TFT_BLACK;
uint16_t fg = TFT_WHITE;

#define SEALEVELPRESSURE_HPA (1013.25)
Adafruit_BME280 bme; // I2C

void refresh_readings();
void refresh_clock();
void wifiStatus();
void indicators();

const char* wl_status_to_string(wl_status_t status);

Timezone sydneyTZ;

//tasks
Task t1_bme280(30000, TASK_FOREVER, &refresh_readings);
Task t2_clock(1000, TASK_FOREVER, &refresh_clock);
Task t5_indicators(2000, TASK_FOREVER, &indicators);
Scheduler runner;

#define LED_PIN            17
#define IFTTT_PIN          16

// Adafruit.IO feeds
// Avoid underscores in the feed names, they cause problems with groupings.
AdafruitIO_Feed *temperature    = io.feed("lab-environment.temperature");
AdafruitIO_Feed *humidity       = io.feed("lab-environment.humidity");
AdafruitIO_Feed *barpressure    = io.feed("lab-environment.barpressure");
AdafruitIO_Feed *altitude       = io.feed("lab-environment.altitude");
AdafruitIO_Feed *led_controller = io.feed("lab-environment.led");

void IRAM_ATTR resetModule() {
  ets_printf("reboot\n");
  esp_restart();
}

void setup() {

  Serial.begin(115200);

  EEPROM.begin(EEPROM_SIZE);  // Setup the EEPROM where we'll write and read the max number of
  // POSTs
  if (EEPROM.readInt(0) < 0)
  {
    EEPROM.writeInt(0, 0); // If the value stored in EEPROM is negative, then initialise to zero
    EEPROM.commit();
  }

  //Setup the hardware interrupt
  //This will reboot the ESP32 if it hangs
  timer = timerBegin(0, 80, true); //timer 0, div 80, due to the ESP32 80Mhz clock speed
  timerAttachInterrupt(timer, &resetModule, true);
  timerAlarmWrite(timer, wdtTimeout  * 1000, false); //set time in us (microseconds)
                                                     // The third parameter is for autoreload, 
                                                     // which is not needed for our purposes.
                                                     // If this interrupt "fires", the device
                                                     // will reboot.
  timerAlarmEnable(timer); //enable interrupt

  pinMode(LED_PIN, OUTPUT);
  pinMode(IFTTT_PIN, OUTPUT);
  tft.init();

  if (!SPIFFS.begin()) {
    DEBUGPRINTLN("SPIFFS initialisation failed!");
    while (1) yield(); // Stay here twiddling thumbs waiting
  }


  // Calibrate the touch interface
  // This only needs to be done once
  // The calibration data will be stored in the SPIFS
  // calibrate_touch_screen();
  DEBUGPRINTLN("\r\nInitialisation done.");


  // Calibrate the touch interface
  // This only needs to be done once
  // The calibration data will be stored in the SPIFS
  // It is important to calibrate the touch interface after the display is rotated
  calibrate_touch_screen();

  tft.setRotation(1);
  tft.setTextColor(fg, bg);
  tft.loadFont("SansSerif-36"); // Create TTF fonts using instructions at https://pages.uoregon.edu/park/Processing/process5.html

  tft.fillScreen(bg);

  DEBUGPRINTLN("\r\nInitialisation done.");

  tft.setCursor(0, 0);
  tft.println("Connecting to");
  tft.println("Wifi");

  drawBmp("/te.bmp", 160, 198);

  bool status;
  // default settings
  // (you can also pass in a Wire library object like &Wire2)
  status = bme.begin(0x76);
  if (!status) {
    DEBUGPRINTLN("Could not find a valid BME280 sensor, check wiring!");
    while (1);
  }
  DEBUGPRINTLN();

  DEBUGPRINT("Attempting to connect to SSID: ");
  DEBUGPRINTLN(WIFI_SSID);
  
  wifiStatus();

  // Connect to Wifi and Adafruit.IO
  io.connect();

  wifiStatus();
  // set up a message handler for the count feed.
  // the handleMessage function (defined below)
  // will be called whenever a message is
  // received from adafruit io.
  led_controller->onMessage(ledMessage);

  // wait for an MQTT connection
  // NOTE: when blending the HTTP and MQTT API, always use the mqttStatus
  // method to check on MQTT connection status specifically
  while (io.mqttStatus() < AIO_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  led_controller->get(); //get the last value for the LED controller

  runner.init();

  DEBUGPRINTLN("Initialized scheduler");

  runner.addTask(t2_clock);         // The order by which the tasks are added to the runner
  // is important. It is best to add the light tasks first,
  // and then the heavier ones.
  runner.addTask(t1_bme280);

  t2_clock.enable();
  t1_bme280.enable();

  waitForSync(); // Get the time and date from NTP

  //  Timezone sydneyTZ;
  sydneyTZ.setLocation(F("Australia/Sydney"));

  // we are connected
  DEBUGPRINTLN();

  tft.fillScreen(bg);
  tft.setCursor(0, 0);
  tft.println("Connected.");
  tft.println("Continuing.");
  drawBmp("/te.bmp", 160, 198);
  delay(1000);
  tft.fillScreen(bg);
  drawBmp("/te.bmp", 160, 198);

  tft.loadFont("NotoSansBold15");
  tft.setTextColor(TFT_LIGHTGREY, bg);
  tft.setCursor(220, 120);
  tft.print("Bytes free"); // print this header
}

void loop() {
  timerWrite(timer, 0); //reset timer (feed watchdog)
  io.run();
  events();  //By default, update the time from NTP every 30 minutes
  runner.execute();

  readTouch();
}
