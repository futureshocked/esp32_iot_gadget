#include <Arduino.h>
#include "car.h"

void Car::print_chassis_id(){     // The "::" operator indicates that print_chassis_id belongs to the Car class
        Serial.print("Vehicle chassis id:");
        Serial.print(Car::_chassis_id);
      }

void Car::set_chassis_id(String chassis_id){      // The "::" operator indicates that set_chassis_id belongs to the Car class
        Car::_chassis_id = chassis_id;
      }

String Car::get_color(){
  switch(Car::color)
  {
    case blue: return "Blue";
    case red: return "Red";
    case white: return "White";
    case green: return "Green";
    case yellow: return "Yellow";
  }
}

Car::Car(String car_make, String car_model, int car_year_of_manufacture){  // This is the constructor
  Car::make                 = car_make;
  Car::model                = car_model;
  Car::year_of_manufacture  = car_year_of_manufacture;
}

void Car::print_car_attributes(){
  Serial.print("Vehicle make: ");
  Serial.println(Car::make);
  Serial.print("Vehicle model: ");
  Serial.println(Car::model);
  Serial.print("Vehicle year of manufacture: ");
  Serial.println(Car::year_of_manufacture);
  Serial.print("Vehicle color: ");
  Serial.println(Car::get_color());
  Serial.print("Vehicle registration number: ");
  Serial.println(Car::registration_number);
  Car::print_chassis_id();
}
