#ifndef SETTINGS_H
#define SETTINGS_H
    #define LED_BUILTIN 2           // This is valid for my devkit
    #include <TFT_eSPI.h>           // ESP32 Hardware-specific library
    #include "AdafruitIO_WiFi.h"   // Beware, at the time of writting this, the Adafruit library needs platform-espressif32 version 1.7.0, https://github.com/platformio/platform-espressif32/releases, specified in platform.io
    #include "network_config.h"
    #include "aux_functions.h"      // Helpful functions
    #include "clock.h"
    
    #define LED_PIN            17
    #define IFTTT_PIN          16
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

