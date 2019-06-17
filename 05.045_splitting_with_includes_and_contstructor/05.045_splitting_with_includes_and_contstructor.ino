/*  05.045 - Multi-file program using header files example

   This sketch contains an example on how to split your program into 
   multiple files. Instead of letting the Arduino IDE to handle joining
   and linking the ino files, we'll use proper C++ structure using 
   .h, .cpp, and #include.
   
   Look at the comments for more information.


   Components
   ----------
    - ESP32 Dev Kit v4

    IDE
    ---
    Arduino IDE with ESP32 Arduino Code
    (https://github.com/espressif/arduino-esp32)


    Libraries
    ---------
    -

   Connections
   -----------


    Other information
    -----------------
    Use this sketch along side the video lecture 05.050 of ESP32 Project: Make an IOT gadget
    Read about the build process in the Arduino IDE: https://github.com/arduino/Arduino/wiki/Build-Process

    Created on June 10 2019 by Peter Dalmaris

*/

#include "car.h"

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  
  Car my_car("Tesla", "X", 2019);
  my_car.color = white;
  my_car.registration_number = "ABC123";
  my_car.set_chassis_id("ASSSD12312312DDFF");
  my_car.print_car_attributes();
}

void loop() {
  // put your main code here, to run repeatedly:

}
