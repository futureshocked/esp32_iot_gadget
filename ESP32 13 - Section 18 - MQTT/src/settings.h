// #define DEBUGLOG   // Turn on debugging messages

#ifndef SETTINGS_H
#define SETTINGS_H
    #include <TFT_eSPI.h>           // ESP32 Hardware-specific library
    #include "AdafruitIO_WiFi.h"   // Beware, at the time of writting this, the Adafruit library needs platform-espressif32 version 1.7.0, https://github.com/platformio/platform-espressif32/releases, specified in platform.io
    #include "network_config.h"
    #include "FS.h"                 // For handling files
    #include "SPIFFS.h"             // Use SPIFFS
    #include "aux_functions.h"      // Helpful functions
    #include "clock.h"
    #include "EEPROM.h"
    #include "esp_system.h"         // To implement the watchdog
    #include "mqtt_controller.h"
    
    #define LED_PIN             17
    #define IFTTT_PIN           12
    #define WIFI_LED            16

    #define TFT_BACKGROUND     TFT_BLACK
    #define TFT_TEXT           TFT_WHITE

    #define EEPROM_SIZE 4   // We'll use 2 bytes in the EEPROM to store the max number of POSTs
                            // MQTT posts where completed in the current power cycle
    #define EEPROM_INDEX 0
    
    #define CALIBRATION_FILE "/tft-touch-calData13" // This file will contain the data from the 
                                                  // touchscreen calibration process at boot (only needed once)

#endif

#ifdef DEBUGLOG
    #define DEBUGPRINT(x)       Serial.print (x)
    #define DEBUGPRINTDEC(x)    Serial.print (x, DEC)
    #define DEBUGPRINTLN(x)     Serial.println (x)
#else
    #define DEBUGPRINT(x)
    #define DEBUGPRINTDEC(x)
    #define DEBUGPRINTLN(x)
#endif


