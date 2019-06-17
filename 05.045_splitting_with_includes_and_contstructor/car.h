#ifndef Car_h
#define Car_h

enum Color   // Because enums show their index instead of their label when printed,
{            // use a function to show the names.
  blue,
  red,
  white,
  green,
  yellow
};

class Car {   // Class name starts with a capital letter
    public:
      Car(String car_make, String car_model, int car_year_of_manufacture);
      String make;  // You can make this private if prefered, and use the contrstuctor only
      String model; // You can make this private if prefered, and use the contrstuctor only
      int year_of_manufacture; // You can make this private if prefered, and use the contrstuctor only
      String get_color();
      String registration_number;
      void print_chassis_id();  // You can also implement a method inside the header file
      void set_chassis_id(String chassis_id);
      void print_car_attributes();
      Color color;

    private:
      String _chassis_id;
};

#endif
