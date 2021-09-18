#include <Arduino.h>
#include "settings.h"

// uint16_t bg = TFT_BLACK;
// uint16_t fg = TFT_WHITE;

// void refresh_clock(TFT_eSPI* tft, Timezone* timezone);
void printLocalTime();
void refresh_clock(TFT_eSPI* tft);