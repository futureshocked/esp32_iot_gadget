#include "mqtt_controller.h"

void ledMessage(AdafruitIO_Data *data) {

  DEBUGPRINT("received <- ");
  DEBUGPRINTLN(data->value());
  
  if (!strcmp(data->value(), "off")) {
    digitalWrite(IFTTT_PIN, LOW);
  }

  if (!strcmp(data->value(), "on")) {
    digitalWrite(IFTTT_PIN, HIGH);    
  }

}