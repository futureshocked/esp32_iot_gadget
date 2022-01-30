#include <Arduino.h>
//#define DEBUGLOG
#define _TASK_PRIORITY 
#include "settings.h"
#include "sensor_readings.h"
#include "bmp_functions.h"
#include <TaskScheduler.h>
#include "network_config.h"
#include <esp_task_wdt.h>  // I'll be using the Task Watchdog Timer (TWDT)

void sensor_readings_update();
void update_indicators();
void clock_update();
volatile byte using_tft = 0; // functions will use this var to check if another function is accessing the tft.
                             // this will prevent conflict which can lead to a crush.                        

const char* ntpServer = "pool.ntp.org";
const long  gmtOffset_sec = 36000;  // Sydney is GMT + 10 hours * 60 seconds
const int   daylightOffset_sec = 0; //3600;.
int sensor_update_period_sec = 5; // I am updating the sensor values on the screen inside the clock update function.
                                          // This is because I suspect that when clock and sensor screen update task happen
                                          // to run at the same time, a conflict in the screen update causes the ESP32
                                          // to crash. It will not reboot even with the watchdog.
int env_update_counter = sensor_update_period_sec; // ... so that the sensor values are updated at first loop.

Adafruit_BME280 bme; // I2C

// Setup the watchdog
//hw_timer_t *timer = NULL;
// const int wdtTimeout = 20000;  //time in ms to trigger the watchdog
#define WDT_TIMEOUT 20
int i = 0;
int last = millis();

// The function that the watchdog will call to reset the device 
// void IRAM_ATTR resetModule() {
//   ets_printf("reboot\n");
//   esp_restart();
// }

TFT_eSPI tft = TFT_eSPI(); 

uint16_t bg = TFT_BLACK;
uint16_t fg = TFT_WHITE;

//tasks
Scheduler runner;
//Scheduler high_priority;
Task t1_bme280(30000, TASK_FOREVER, &sensor_readings_update); // normal rate: 10000
Task t2_clock(500, TASK_FOREVER, &clock_update); // normal rate 1000
Task t5_indicators(500, TASK_FOREVER, &update_indicators); // normal rate 2000


// Adafruit.IO feeds
// Avoid underscores in the feed names, they cause problems with groupings.
AdafruitIO_WiFi io(IO_USERNAME, IO_KEY, WIFI_SSID, WIFI_PASS);
AdafruitIO_Feed *temperature    = io.feed("lab-environment.temperature");
AdafruitIO_Feed *humidity       = io.feed("lab-environment.humidity");
AdafruitIO_Feed *barpressure    = io.feed("lab-environment.barpressure");
AdafruitIO_Feed *altitude       = io.feed("lab-environment.altitude");
AdafruitIO_Feed *led_controller = io.feed("lab-environment.led");
AdafruitIO_Feed *aio_loger      = io.feed("lab-environment.aio_logger");

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
  // timer = timerBegin(0, 80, true); //timer 0, div 80, due to the ESP32 80Mhz clock speed
  // timerAttachInterrupt(timer, &resetModule, true);
  // timerAlarmWrite(timer, wdtTimeout  * 1000, false); //set time in us
  // timerAlarmEnable(timer); //enable interrupt


  // Implementing watchdog. See https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/system/wdts.html
  esp_task_wdt_init(WDT_TIMEOUT, true); //enable panic so ESP32 does a hard restart if timeout period elapses
  esp_task_wdt_add(NULL); //add current thread to WDT watch

  delay(500);

  DEBUGPRINTLN("EEPROM...");
  tft.print("Checking EEPROM... ");

  EEPROM.begin(EEPROM_SIZE); // Setup the EEPROM where we'll write and read the max number of
  // POSTs
  tft.println(EEPROM.readUInt(EEPROM_INDEX));
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

  aio_loger     ->save("Setup complete.");
  
  DEBUGPRINTLN("Setup complete");
}

void loop() {
  esp_task_wdt_reset(); // Reset the Task Watchdog Timer (TWDT) so that device does not reset
  
  // timerWrite(timer, 0); //reset timer (feed watchdog)
  // To test the watchdog, uncomment the next line:
  // delay(15000);

  runner.execute();

  // Update the MQTT queue and stay connected to Adafruit IO
  io.run();

  // Check for touch events
  if (using_tft == 0) // Check "using screen" flag
  {
    using_tft = 1; // Raise "using screen" flag
    readTouch( &tft );
    using_tft = 0; // Drop "using screen" flag
  }
}

void sensor_readings_update()
{
  // called by t1_bme280 task
  if (using_tft == 0) // Check "using screen" flag
  {
    // Screen not being used, Ok to continue
    using_tft = 1; // Raise "using screen" flag

    refresh_readings( &bme, 
                    &tft,
                    temperature,
                    humidity,
                    barpressure,
                    altitude,
                    aio_loger);
    using_tft = 0; // Drop "using screen" flag
  }
}

void clock_update()
{
  // called by t2_clock task
  if (using_tft == 0) // Check "using screen" flag
  {
    // Screen not being used, Ok to continue
    using_tft = 1; // Raise "using screen" flag
    Serial.print(io.statusText());
    Serial.print(" ");
    Serial.println(millis());
    // printLocalTime();
    refresh_clock(&tft);
    using_tft = 0; // Drop "using screen" flag
  }

}

void update_indicators()
{
  // called by t5_indicators task
  if (using_tft == 0)  // Check "using screen" flag
  {
    // Screen not being used, Ok to continue
    using_tft = 1; // Raise "using screen" flag
    indicators(&tft, &io);
    using_tft = 0; // Drop "using screen" flag
  }
}