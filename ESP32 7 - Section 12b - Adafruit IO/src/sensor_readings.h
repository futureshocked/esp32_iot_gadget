#ifndef SENSOR_READINGS_H
#define SENSOR_READINGS_H

    #include <Adafruit_Sensor.h>
    #include <Adafruit_BME280.h>
    #include <TFT_eSPI.h>
    #define SEALEVELPRESSURE_HPA (1013.25)

    void refresh_readings(Adafruit_BME280* bme, TFT_eSPI* tft);

#endif

#include "settings.h"

