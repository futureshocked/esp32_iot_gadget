/*  05.030 - Namespaces example

   This sketch contains an example on how to use namespaces.
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
    Use this sketch along side the video lecture 05.030 of ESP32 Project: Make an IOT gadget

    Created on June 10 2019 by Peter Dalmaris

*/

namespace car {
  int engine_capacity;
  int color;
}

namespace motorcycle {
  int engine_capacity;
  int color;
}

void setup() {
  Serial.begin(9600);

  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  // My car's specs
  car::color = 1;
  car::engine_capacity = 2000;
  Serial.println("My car's specs:");
  Serial.print("Color: ");
  Serial.println(car::color );
  Serial.print("Engine capacity: ");
  Serial.println(car::engine_capacity );

  // My motorcycles's specs
  motorcycle::color = 2;
  motorcycle::engine_capacity = 200;
  Serial.println("My motorcyclesr's specs:");
  Serial.print("Color: ");
  Serial.println(motorcycle::color );
  Serial.print("Engine capacity: ");
  Serial.println(motorcycle::engine_capacity );

}

void loop() {
  // put your main code here, to run repeatedly:
}
