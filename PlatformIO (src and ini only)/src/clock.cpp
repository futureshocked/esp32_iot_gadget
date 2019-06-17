#include "clock.h"

void refresh_clock(TFT_eSPI* tft, Timezone* timezone)
{
  //See documentation for ezTime options: https://github.com/ropg/ezTime
  tft->loadFont("NotoSansBold15");
  tft->setTextColor(TFT_LIGHTGREY, TFT_BLACK);  // See available colors at https://github.com/Bodmer/TFT_eSPI/blob/master/TFT_eSPI.h
  //Clear the date area
  tft->fillRect(220, 50, 135, 70, TFT_BLACK);
  // Day of week, day of month
  tft->setCursor(220, 50);
  tft->print(timezone->dateTime("l")); // Day of week
  // Month and day of month
  tft->setCursor(220, 65);
  tft->print(timezone->dateTime("F")); // Month
  tft->print(" ");
  tft->print(timezone->dateTime("j"));  // Day of month
  // Year
  tft->setCursor(220, 80);
  tft->print(timezone->dateTime("Y")); // Year
  // Time
  tft->setCursor(220, 95);
  tft->print(timezone->dateTime("H:i:s")); // Time

//   indicators();
}