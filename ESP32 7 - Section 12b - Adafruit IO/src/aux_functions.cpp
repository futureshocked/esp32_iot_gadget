#include <Arduino.h>
#include "settings.h"

void indicators()
{
  digitalWrite(LED_PIN, HIGH);
  digitalWrite(LED_PIN, LOW);
}

// void wifiStatus()
// {
  // Wifi status
//   tft.loadFont("NotoSansBold15");
//   tft.setTextColor(TFT_LIGHTGREY, bg);
//   tft.fillRect(5, 220, 150, 20, bg);
//   tft.setCursor(5, 220);
//   tft.print(wl_status_to_string(WiFi.status()));
  //  tft.print(io.networkStatus());
// }

