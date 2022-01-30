#include <Arduino.h>
#include "settings.h"

const char* wl_status_to_string(wl_status_t status);

void wifiStatus(    TFT_eSPI* tft, 
                    AdafruitIO_WiFi* io);

void indicators(    TFT_eSPI* tft, 
                    AdafruitIO_WiFi* io);

void postsCounter(  TFT_eSPI* tft, AdafruitIO_Feed* logger);

void calibrate_touch_screen(TFT_eSPI* tft);

void readTouch(TFT_eSPI* tft);

void heapSize(TFT_eSPI* tft);