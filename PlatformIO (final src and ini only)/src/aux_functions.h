#include <Arduino.h>
#include "settings.h"

void wifiStatus(    TFT_eSPI* tft, 
                    AdafruitIO_WiFi* io);

const char* wl_status_to_string(wl_status_t status);

void postsCounter(  TFT_eSPI* tft);

void readTouch(TFT_eSPI* tft);

void calibrate_touch_screen(TFT_eSPI* tft);