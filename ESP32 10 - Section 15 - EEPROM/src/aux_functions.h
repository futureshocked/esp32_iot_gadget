#include <Arduino.h>
#include "settings.h"

// uint16_t bg = TFT_BLACK;
// uint16_t fg = TFT_WHITE;
// #ifndef POSTCOUNTER_H
//     #define POSTCOUNTER_H
    // int postCounter = 0;
// #endif

const char* wl_status_to_string(wl_status_t status);

void wifiStatus(    TFT_eSPI* tft, 
                    AdafruitIO_WiFi* io);

void indicators(    TFT_eSPI* tft, 
                    AdafruitIO_WiFi* io);

void postsCounter(  TFT_eSPI* tft);

