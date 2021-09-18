#include <Arduino.h>
#include "settings.h"

// uint16_t bg = TFT_BLACK;
// uint16_t fg = TFT_WHITE;

void wifiStatus(    TFT_eSPI* tft, 
                    AdafruitIO_WiFi* io);

void indicators(    TFT_eSPI* tft, 
                    AdafruitIO_WiFi* io);

const char* wl_status_to_string(wl_status_t status);