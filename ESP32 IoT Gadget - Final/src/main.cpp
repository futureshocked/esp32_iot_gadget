#include <Arduino.h>
//#define DEBUGLOG
#include "settings.h"
#include "sensor_readings.h"
#include "bmp_functions.h"
#include <TaskScheduler.h>
#include "network_config.h"

void sensor_readings_update();
void update_indicators();
void clock_update();

const char* ntpServer = "pool.ntp.org";
const long  gmtOffset_sec = 36000;  // Sydney is GMT + 10 hours * 60 seconds
const int   daylightOffset_sec = 0; //3600;.

Adafruit_BME280 bme; // I2C

// Setup the watchdog
hw_timer_t *timer = NULL;
const int wdtTimeout = 30000;  //time in ms to trigger the watchdog

// The function that the watchdog will call to reset the device 
void IRAM_ATTR resetModule() {
  ets_printf("reboot\n");
  esp_restart();
}

TFT_eSPI tft = TFT_eSPI(); 

uint16_t bg = TFT_BLACK;
uint16_t fg = TFT_WHITE;

//tasks
Task t1_bme280(30000, TASK_FOREVER, &sensor_readings_update);
Task t2_clock(1000, TASK_FOREVER, &clock_update); 
Task t5_indicators(2000, TASK_FOREVER, &update_indicators);
Scheduler runner;

// Adafruit.IO feeds
// Avoid underscores in the feed names, they cause problems with groupings.
AdafruitIO_WiFi io(IO_USERNAME, IO_KEY, WIFI_SSID, WIFI_PASS);
AdafruitIO_Feed *temperature    = io.feed("lab-environment.temperature");
AdafruitIO_Feed *humidity       = io.feed("lab-environment.humidity");
AdafruitIO_Feed *barpressure    = io.feed("lab-environment.barpressure");
AdafruitIO_Feed *altitude       = io.feed("lab-environment.altitude");
AdafruitIO_Feed *led_controller = io.feed("lab-environment.led");

void setup() {
  // put your setup code here, to run once:
  pinMode(LED_PIN,OUTPUT);
  pinMode(IFTTT_PIN, OUTPUT);
  pinMode(WIFI_LED, OUTPUT);

  Serial.begin(9600);
  DEBUGPRINT("Starting with debug messages");

    // Setup the TFT
  DEBUGPRINTLN("TFT...");
  tft.begin();

  // Calibrate the touch interface
  // This only needs to be done once
  // The calibration data will be stored in the SPIFS
  // It is important to calibrate the touch interface after the display is rotated
  DEBUGPRINTLN("Touch...");
  calibrate_touch_screen(&tft);

  tft.setRotation(1);
  tft.setTextColor(TFT_TEXT, TFT_BACKGROUND);
  
  tft.fillScreen(TFT_BACKGROUND);
  tft.loadFont("NotoSansBold15");
  tft.setCursor(0, 0);
  tft.println("Hello!");
  delay(500);

  // Setup the hardware interrupt
  // This will reboot the ESP32 if it hangs
  DEBUGPRINTLN("Timers...");
  tft.println("Setting timers...");
  timer = timerBegin(0, 80, true); //timer 0, div 80, due to the ESP32 80Mhz clock speed
  timerAttachInterrupt(timer, &resetModule, true);
  timerAlarmWrite(timer, wdtTimeout  * 1000, false); //set time in us
  timerAlarmEnable(timer); //enable interrupt
  delay(500);

  DEBUGPRINTLN("EEPROM...");
  tft.println("Checking EEPROM...");
  EEPROM.begin(EEPROM_SIZE); // Setup the EEPROM where we'll write and read the max number of
  // POSTs
  if (EEPROM.readUInt(EEPROM_INDEX) < 0)
  {
    EEPROM.writeUInt(EEPROM_INDEX, 0); // If the value stored in EEPROM is negative, then initialise to zero
    EEPROM.commit();
  }
  delay(500);

  DEBUGPRINTLN("SPIFFS...");
  tft.println("Starting SPIFFS...");
  if (!SPIFFS.begin()) {
    Serial.println("SPIFFS initialisation failed!");
    while (1) yield(); // Stay here twiddling thumbs waiting
  }
  delay(500);

  tft.println("Starting BME sensor...");
  bool status;
  // (you can also pass in a Wire library object like &Wire2)
  DEBUGPRINTLN("BME sensor...");
  status = bme.begin(0x76);

  if (!status) {
    Serial.println("Could not find a valid BME280 sensor, check wiring!");
    while (1);
  }
  delay(500);

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

  // set up a message handler for the count feed.
  // the handleMessage function (defined below)
  // will be called whenever a message is
  // received from adafruit io.
  DEBUGPRINTLN("MQTT controller...");
  tft.println("Setting the MQTT controller...");
  led_controller->onMessage(ledMessage);


  tft.println("Starting the task scheduler...");
  // Start the task scheduler
  DEBUGPRINTLN("Scheduler...");
  // Start the task scheduler
  runner.init();

  // Add tasks to runner
  runner.addTask(t1_bme280);
  runner.addTask(t2_clock);
  runner.addTask(t5_indicators);

  // Enable the tasks
  t1_bme280.enable();
  t2_clock.enable();
  t5_indicators.enable();
  delay(500);

  tft.println("Ready!");
  delay(2000);

  tft.fillScreen(TFT_BACKGROUND);
  drawBmp("/te.bmp", 160, 198, &tft);
  wifiStatus(&tft, &io);

  tft.loadFont("NotoSansBold15");
  tft.setTextColor(TFT_LIGHTGREY, TFT_BACKGROUND);
  tft.setCursor(230, 135);
  tft.print("HEAP MEM");
  
  tft.setCursor(10, 0);
  tft.loadFont("SansSerif-36");
  tft.println("Right now...");
  
  DEBUGPRINTLN("Setup complete");
}

void loop() {
  timerWrite(timer, 0); //reset timer (feed watchdog)
  // To test the watchdog, uncomment the next line:
  // delay(15000);

  runner.execute();

  // Update the MQTT queue and stay connected to Adafruit IO
  io.run();

  // Check for touch events
  readTouch( &tft );
}

void sensor_readings_update()
{
  refresh_readings( &bme, 
                    &tft,
                    temperature,
                    humidity,
                    barpressure,
                    altitude);
  
  wifiStatus(&tft, &io);
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