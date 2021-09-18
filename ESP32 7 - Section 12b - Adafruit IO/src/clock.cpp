#include "clock.h"

void refresh_clock(TFT_eSPI* tft)
{
  struct tm timeinfo;
  tft->fillRect(190, 50, 10, 10, TFT_WHITE);
  if(!getLocalTime(&timeinfo)){
    Serial.println("Failed to obtain time");
    tft->fillRect(190, 50, 10, 10, TFT_BLACK);
    return;
  }
  
  tft->loadFont("NotoSansBold15");
  tft->setTextColor(TFT_LIGHTGREY, TFT_BLACK);  // See available colors at https://github.com/Bodmer/TFT_eSPI/blob/master/TFT_eSPI.h
  //Clear the date area
  tft->fillRect(200, 50, 135, 70, TFT_BLACK);
  // Day of week, day of month
  tft->setCursor(200, 50);
  tft->print(&timeinfo, "%A"); // Day of week
  // Month and day of month
  tft->setCursor(200, 65);
  tft->print(&timeinfo, "%B"); // Month
  tft->print(" ");
  tft->print(&timeinfo, "%d");  // Day of month
  // Year
  tft->setCursor(200, 80);
  tft->print(&timeinfo, "%Y"); // Year
  // Time
  tft->setCursor(200, 95);
  tft->print(&timeinfo, "%H:%M:%S"); // Time

  tft->fillRect(190, 50, 10, 10, TFT_BLACK);

//   indicators();
}

void printLocalTime(){
  struct tm timeinfo;
  if(!getLocalTime(&timeinfo)){
    Serial.println("Failed to obtain time");
    return;
  }
  Serial.println(&timeinfo, "%A, %B %d %Y %H:%M:%S");
  Serial.print("Day of week: ");
  Serial.println(&timeinfo, "%A");
  Serial.print("Month: ");
  Serial.println(&timeinfo, "%B");
  Serial.print("Day of Month: ");
  Serial.println(&timeinfo, "%d");
  Serial.print("Year: ");
  Serial.println(&timeinfo, "%Y");
  Serial.print("Hour: ");
  Serial.println(&timeinfo, "%H");
  Serial.print("Hour (12 hour format): ");
  Serial.println(&timeinfo, "%I");
  Serial.print("Minute: ");
  Serial.println(&timeinfo, "%M");
  Serial.print("Second: ");
  Serial.println(&timeinfo, "%S");

  Serial.println("Time variables");
  char timeHour[3];
  strftime(timeHour,3, "%H", &timeinfo);
  Serial.println(timeHour);
  char timeWeekDay[10];
  strftime(timeWeekDay,10, "%A", &timeinfo);
  Serial.println(timeWeekDay);
  Serial.println();
}

