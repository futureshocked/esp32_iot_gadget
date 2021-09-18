#include <Arduino.h>
#include "sensor_readings.h"
#include "TFT_eSPI.h"         // ESP32 Hardware-specific library
#include "settings.h"         // The order is important!
#include "bmp_functions.h"
#include "TaskScheduler.h"
#include "network_config.h"

// SPIFFS plugin for the Arduino IDE: https://github.com/me-no-dev/arduino-esp32fs-plugin

// In this version of the program, start using git.
// In the project root, do "git init", "git add .", "git commit -am "First commit"".
// Once this is done, Code will be showing the changed files in the Source Control pane.

void sensor_readings_update();
void clock_update();

const char* ntpServer = "pool.ntp.org";
const long  gmtOffset_sec = 36000;  // Sydney is GMT + 10 hours * 60 seconds
const int   daylightOffset_sec = 0; //3600;

Adafruit_BME280 bme;

TFT_eSPI tft = TFT_eSPI();       // Invoke custom library

uint16_t bg = TFT_BLACK;
uint16_t fg = TFT_WHITE;

// Setup tasks for the task scheduler
// The third argument taks a pointer to a function, but cannot have parameters.
Task t1_bme280(2000, TASK_FOREVER, &sensor_readings_update);
Task t2_clock(1000, TASK_FOREVER, &clock_update);

// Create the scheduler
Scheduler runner;

void setup() {
  pinMode(LED_BUILTIN,OUTPUT);
  Serial.begin(9600);

  if (!SPIFFS.begin()) {
    tft.println("SPIFFS initialisation failed!");
    while (1) yield(); // Stay here twiddling thumbs waiting
  }

  // Setup the TFT
  tft.begin();

  tft.setRotation(1);
  tft.setTextColor(fg, bg);

  tft.fillScreen(bg);

  tft.setCursor(0, 0);
  tft.println("Hello!");
  tft.println("Starting BME sensor...");
  delay(1000);

  bool status;
  // (you can also pass in a Wire library object like &Wire2)
  status = bme.begin(0x76);
  if (!status) {
    Serial.println("Could not find a valid BME280 sensor, check wiring!");
    while (1);
  }

  // Connect to Wifi
  Serial.println("Connecting to Wifi...");
  io.connect();
  
  // wait for a connection
  while(io.status() < AIO_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  // Check the Wifi status
  Serial.println(io.statusText());

  // Configure the clock.
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);

  // Start the task scheduler
  runner.init();

  // Add the task to the scheduler
  runner.addTask(t1_bme280);
  runner.addTask(t2_clock);

  // Enable the task
  t1_bme280.enable();
  t2_clock.enable();

  tft.fillScreen(bg);
  drawBmp("/te.bmp", 160, 198, &tft);
}

void loop() {
  // Execute the scheduler runner
  runner.execute();
}

void sensor_readings_update()
{
  refresh_readings(&bme, &tft);
}

void clock_update()
{
  Serial.println(io.statusText());
  printLocalTime();
  refresh_clock(&tft);
}
