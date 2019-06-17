#ifndef Car_h
#define Car_h

enum Color
{
  blue,
  red,
  white,
  green,
  yellow
};

class Car {   // Class name starts with a capital letter
    public:
      String make;
      String model;
      int year_of_manufacture;
      Color color;
      String registration_number;
      void print_chassis_id();  // You can also implement a method inside the header file
//      void print_chassis_id(){
//        Serial.print("Vehicle chassis id:");
//        Serial.print(_chassis_id);
//      }
      void set_chassis_id(String chassis_id);
//      void set_chassis_id(String chassis_id){
//        _chassis_id = chassis_id;
//      }

    private:
      String _chassis_id;
};

#endif
