/*  05.040 - Multi-file program example

   This sketch contains an example on how to split your program into 
   multiple files.
   
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
    Use this sketch along side the video lecture 05.040 of ESP32 Project: Make an IOT gadget
    Read about the build process in the Arduino IDE: https://github.com/arduino/Arduino/wiki/Build-Process

    Created on June 10 2019 by Peter Dalmaris

*/

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  
  in_file1();
  in_file2();

  // This will not work because I have created the Example_class class in an .ino file.
  // Example_class an_object;
  // an_object.my_function();

  //Serial.println(a_string); // This will not work because "a_string" is declared 
                              // in file "my_variables" which is included after the main
                              // file (where this variable is called).
}

void loop() {
  // put your main code here, to run repeatedly:

}
