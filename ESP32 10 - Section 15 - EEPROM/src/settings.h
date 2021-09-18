
#ifndef SETTINGS_H
#define SETTINGS_H
    #define LED_BUILTIN 2           // This is valid for my devkit
    #include <TFT_eSPI.h>           // ESP32 Hardware-specific library
    #include "AdafruitIO_WiFi.h"   // Beware, at the time of writting this, the Adafruit library needs platform-espressif32 version 1.7.0, https://github.com/platformio/platform-espressif32/releases, specified in platform.io
    #include "network_config.h"
    #include "aux_functions.h"      // Helpful functions
    #include "clock.h"
    #include "EEPROM.h"

    // uint16_t bg = TFT_BLACK;
    // uint16_t fg = TFT_WHITE;
    
    #define LED_PIN            17
    #define IFTTT_PIN          16

    #define EEPROM_SIZE 2  // We'll use 1 byte in the EEPROM to store the max number of POSTs
                            // MQTT posts where completed in the current power cycle

#endif

#ifdef DEBUGLOG
    #define DEBUGPRINT(x)     Serial.print (x)
    #define DEBUGPRINTDEC(x)     Serial.print (x, DEC)
    #define DEBUGPRINTLN(x)  Serial.println (x)
#else
    #define DEBUGPRINT(x)
    #define DEBUGPRINTDEC(x)
    #define DEBUGPRINTLN(x)
#endif


