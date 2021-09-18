#include <Arduino.h>
#include "settings.h"         // The order is important!
#include "sensor_readings.h"
#include "TFT_eSPI.h"         // ESP32 Hardware-specific library
#include "bmp_functions.h"  
#include "TaskScheduler.h"

// SPIFFS plugin for the Arduino IDE: https://github.com/me-no-dev/arduino-esp32fs-plugin

// In this version of the program, start using git.
// In the project root, do "git init", "git add .", "git commit -am "First commit"".
// Once this is done, Code will be showing the changed files in the Source Control pane.

void sensor_readings_update();
void update_indicators();
void clock_update();

const char* ntpServer = "pool.ntp.org";
const long  gmtOffset_sec = 36000;  // Sydney is GMT + 10 hours * 60 seconds
const int   daylightOffset_sec = 0; //3600;

Adafruit_BME280 bme;

// Setup the watchdog
hw_timer_t *timer = NULL;
const int wdtTimeout = 30000;  //time in ms to trigger the watchdog

// The function that the watchdog will call to reset the device 
void IRAM_ATTR resetModule() {
  ets_printf("reboot\n");
  esp_restart();
}

TFT_eSPI tft = TFT_eSPI();       // Invoke custom library

uint16_t bg = TFT_BLACK;
uint16_t fg = TFT_WHITE;

// Setup tasks for the task scheduler
// The third argument taks a pointer to a function, but cannot have parameters.
Task t1_bme280(10000, TASK_FOREVER, &sensor_readings_update); 
Task t2_clock(1000, TASK_FOREVER, &clock_update); 
Task t5_indicators(2000, TASK_FOREVER, &update_indicators);

// Create the scheduler
Scheduler runner;

// AdafruitIO_WiFi io(IO_USERNAME, IO_KEY, WIFI_SSID, WIFI_PASS);
AdafruitIO_WiFi io(IO_USERNAME, IO_KEY, WIFI_SSID, WIFI_PASS);

// Adafruit.IO feeds
// Avoid underscores in the feed names, they cause problems with groupings.
AdafruitIO_Feed *temperature    = io.feed("lab-environment.temperature");
AdafruitIO_Feed *humidity       = io.feed("lab-environment.humidity");
AdafruitIO_Feed *barpressure    = io.feed("lab-environment.barpressure");
AdafruitIO_Feed *altitude       = io.feed("lab-environment.altitude");
AdafruitIO_Feed *led_controller = io.feed("lab-environment.led");

void setup() {
  pinMode(LED_BUILTIN,OUTPUT);
  Serial.begin(9600);

  // Setup the hardware interrupt
  // This will reboot the ESP32 if it hangs
  timer = timerBegin(0, 80, true); //timer 0, div 80, due to the ESP32 80Mhz clock speed
  timerAttachInterrupt(timer, &resetModule, true);
  timerAlarmWrite(timer, wdtTimeout  * 1000, false); //set time in us
  timerAlarmEnable(timer); //enable interrupt

  EEPROM.begin(EEPROM_SIZE); // Setup the EEPROM where we'll write and read the max number of
  // POSTs
  if (EEPROM.readInt(0) < 0)
  {
    EEPROM.writeInt(0, 0); // If the value stored in EEPROM is negative, then initialise to zero
    EEPROM.commit();
  }

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
  tft.loadFont("NotoSansBold15");
  tft.println("Hello!");
  tft.println("Starting BME sensor...");
  delay(1000);
  // tft.println();
  // tft.setCursor(0, 50);
  bool status;
  // (you can also pass in a Wire library object like &Wire2)
  status = bme.begin(0x76);
  if (!status) {
    Serial.println("Could not find a valid BME280 sensor, check wiring!");
    tft.println("Could not find a BME sensor...");
    while (1);
  }
  
  //Check the wifi status and print on TFT
  //wifiStatus(&tft, &io);

  // Connect to Wifi
  Serial.println("Connecting to Wifi...");
  tft.println("Connecting to Wifi...");
  io.connect();
  // wait for a connection
  while(io.status() < AIO_CONNECTED) {
    Serial.print(".");
    tft.print(".");
    delay(500);
  }
  delay(500);
  // Check the Wifi status
  tft.println();
  tft.println(io.statusText());
  Serial.println(io.statusText());
  delay(500);
  // Configure the clock.
  tft.println("Configuring the clock...");
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
  delay(500);
  // Check the Wifi status and update TFT
  wifiStatus(&tft, &io);

  // Start the task scheduler
  tft.println("Starting the task scheduler...");
  runner.init();
  delay(500);
  // Add the task to the scheduler
  runner.addTask(t1_bme280);
  runner.addTask(t2_clock);
  runner.addTask(t5_indicators);

  // Enable the task
  t1_bme280.enable();
  t2_clock.enable();
  t5_indicators.enable();

  tft.println("READY!");
  delay(500);

  tft.fillScreen(bg);
  drawBmp("/te.bmp", 160, 198, &tft);
}

void loop() {  
  timerWrite(timer, 0); //reset timer (feed watchdog)
  // To test the watchdog, uncomment the next line:
  // delay(35000);

  // Execute the scheduler runner
  runner.execute();

  // Update the MQTT queue and stay connected to Adafruit IO
  io.run();
}

void sensor_readings_update()
{
  refresh_readings( &bme, 
                    &tft, 
                    temperature, 
                    humidity, 
                    barpressure, 
                    altitude);
}

void clock_update()
{
  Serial.println(io.statusText());
  printLocalTime();
  refresh_clock(&tft);
}

void update_indicators()
{
  indicators(&tft, &io);
}