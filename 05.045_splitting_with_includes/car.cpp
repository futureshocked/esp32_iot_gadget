#include <Arduino.h>
#include "car.h"

void Car::print_chassis_id(){     // The "::" operator indicates that print_chassis_id belongs to the Car class
        Serial.print("Vehicle chassis id:");
        Serial.print(Car::_chassis_id);
      }

void Car::set_chassis_id(String _chassis_id){      // The "::" operator indicates that set_chassis_id belongs to the Car class
        Car::_chassis_id = _chassis_id;
      }
