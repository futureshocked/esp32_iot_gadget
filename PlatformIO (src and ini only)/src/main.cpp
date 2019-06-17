#include <Arduino.h>
//#define DEBUGLOG
#include "settings.h"
#include "sensor_readings.h"
#include "bmp_functions.h"
#include <TaskScheduler.h>
#include "network_config.h"

void sensor_readings_update();
void clock_update();

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
Scheduler runner;

// Setup the clock 
Timezone sydneyTZ;

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
  pinMode(LED_BUILTIN,OUTPUT);
  pinMode(IFTTT_PIN,OUTPUT);
  Serial.begin(9600);
  DEBUGPRINT("Starting with debug messages");

  // Setup the hardware interrupt
  // This will reboot the ESP32 if it hangs
  DEBUGPRINTLN("Timers...");
  timer = timerBegin(0, 80, true); //timer 0, div 80, due to the ESP32 80Mhz clock speed
  timerAttachInterrupt(timer, &resetModule, true);
  timerAlarmWrite(timer, wdtTimeout  * 1000, false); //set time in us
  timerAlarmEnable(timer); //enable interrupt

  DEBUGPRINTLN("EEPROM...");
  EEPROM.begin(EEPROM_SIZE); // Setup the EEPROM where we'll write and read the max number of
  // POSTs
  if (EEPROM.readInt(0) < 0)
  {
    EEPROM.writeInt(0, 0); // If the value stored in EEPROM is negative, then initialise to zero
    EEPROM.commit();
  }

  DEBUGPRINTLN("SPIFFS...");
  if (!SPIFFS.begin()) {
    Serial.println("SPIFFS initialisation failed!");
    while (1) yield(); // Stay here twiddling thumbs waiting
  }

  // Setup the TFT
  DEBUGPRINTLN("TFT...");
  tft.init();

  // Calibrate the touch interface
  // This only needs to be done once
  // The calibration data will be stored in the SPIFS
  // It is important to calibrate the touch interface after the display is rotated
  DEBUGPRINTLN("Touch...");
  calibrate_touch_screen(&tft);

  tft.setRotation(1);
  tft.loadFont("NotoSansBold15"); // Create TTF fonts using instructions at https://pages.uoregon.edu/park/Processing/process5.html
  tft.setTextColor(fg, bg);
  tft.fillScreen(bg);

  tft.setCursor(10, 0);
  tft.println("Hello!");
    tft.setCursor(10, 15);
  tft.println("Starting BME sensor...");
  delay(5000);
  
  bool status;

  // (you can also pass in a Wire library object like &Wire2)
  DEBUGPRINTLN("BME sensor...");
  status = bme.begin(0x76);

  if (!status) {
    Serial.println("Could not find a valid BME280 sensor, check wiring!");
    while (1);
  }

  // Give Wifi connection a little more time to complete
  timerWrite(timer, 0);

  tft.loadFont("NotoSansBold15");
  tft.setCursor(10, 30);
  tft.println("Starting Wifi...");

  //Check the wifi status and print on TFT
  wifiStatus(&tft, &io);

  // Connect to Wifi.
  DEBUGPRINTLN("Wifi...");
  io.connect();

  // Check the Wifi status and update TFT
  wifiStatus(&tft, &io);

  // set up a message handler for the count feed.
  // the handleMessage function (defined below)
  // will be called whenever a message is
  // received from adafruit io.
  DEBUGPRINTLN("MQTT controller...");
  led_controller->onMessage(ledMessage);

  // wait for a connection
  while(io.status() < AIO_CONNECTED) {
      Serial.print(".");
  delay(500);
    }

  tft.loadFont("NotoSansBold15");
  tft.setCursor(10, 45);
  tft.println("Setting the clock...");
  // Setup the clock
  DEBUGPRINTLN("Clock...");
  // Setup the clock
  waitForSync();
  sydneyTZ.setLocation("Australia/Sydney");

  tft.loadFont("NotoSansBold15");
  tft.setCursor(10, 60);
  tft.println("Setting the task scheduler...");
  // Start the task scheduler
  DEBUGPRINTLN("Scheduler...");
  // Start the task scheduler
  runner.init();

  // Add tasks to runner
  runner.addTask(t1_bme280);
  runner.addTask(t2_clock);
  t1_bme280.enable();
  t2_clock.enable();


  tft.loadFont("NotoSansBold15");
  tft.setCursor(10, 75);
  tft.println("Ready!");
  tft.setCursor(10, 90);
  tft.println("Let's do this!");
  delay(2000);

  tft.fillScreen(bg); // Clear the screen
  drawBmp("/te.bmp", 160, 198, &tft);
  wifiStatus(&tft, &io);

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
  refresh_clock(&tft, &sydneyTZ);
}