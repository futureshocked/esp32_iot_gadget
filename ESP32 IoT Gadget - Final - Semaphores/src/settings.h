#ifdef DEBUGLOG
    #define DEBUGPRINT(x)       Serial.print (x)
    #define DEBUGPRINTDEC(x)    Serial.print (x, DEC)
    #define DEBUGPRINTLN(x)     Serial.println (x)
#else
    #define DEBUGPRINT(x)
    #define DEBUGPRINTDEC(x)
    #define DEBUGPRINTLN(x)
#endif

#ifndef SETTINGS_H
    #define SETTINGS_H
    #define LED_BUILTIN 2   // This is valid for my devkit
    #include "TFT_eSPI.h"     // ESP32 Hardware-specific library
    #include "FS.h"                 // For handling files
    #include "SPIFFS.h"             // Use SPIFFS
    #include "AdafruitIO_WiFi.h"
    #include "network_config.h"
    #include "aux_functions.h"      // Helpful functions
    #include "clock.h"
    #include "EEPROM.h"
    #include "esp_system.h"  // To implement the watchdog
    #include "mqtt_controller.h"

    #define TFT_BACKGROUND     TFT_BLACK
    #define TFT_TEXT           TFT_WHITE

    #define LED_PIN             17
    #define IFTTT_PIN           12
    #define WIFI_LED            16

    #define EEPROM_SIZE 4  // We'll use 4 bytes in the EEPROM to store the max number of POSTs
    #define EEPROM_INDEX 0

    #define CALIBRATION_FILE "/tft-touch-calData13" // This file will contain the data from the
                                                  // touchscreen calibration process at boot (only needed once)
#endif

