/*  05.020 - Pointer usage examples

   This sketch contains examples on how to use pointers.
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
    - TFT_eSPI.h   (or you can use any other library you want).
    -

   Connections
   -----------


    Other information
    -----------------
    Use this sketch along side the video lecture 05.020 of ESP32 Project: Make an IOT gadget

    Created on June 10 2019 by Peter Dalmaris

*/

#include <TFT_eSPI.h>

void setup() {
  Serial.begin(9600);

  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  int my_var1 = 15;  // Create a variable and store a value in it.

  // Experiment 1: Find the storage address of a variable
  Serial.print("my_var stores value: ");
  Serial.println(my_var1);
  Serial.print("This variable is stored at location (memory address): ");
  Serial.println((int) &my_var1, HEX);
  Serial.println();

  // Experiment 2: Access the value of a variable using a pointer
  // Access value using a pointer
  Serial.println("Let's access my_var using its pointer instead of the reference name.");
  Serial.print("*my_var_pnt points to memory address &my_var1: ");
  Serial.println((int) &my_var1, HEX);
  Serial.print("This memory address contains value: ");
  int *my_var_pnt = &my_var1;   // Dereference my_var1 and store the variable address in my_var_pnt
  Serial.println(*my_var_pnt);

  // Experiment 3: Change the the value of a variable using a pointer
  Serial.println();
  // Change the value of a variable using a pointer
  // Let's change the value of my_var1 to 16 using pointers
  *my_var_pnt = 16;   // Change the value of my_var1 using its pointer
  // Access value using a pointer
  Serial.println("Access the new value of my_var using its pointer instead of the reference name.");
  Serial.print("*my_var_pnt points to memory address &my_var1: ");
  Serial.println((int) &my_var1, HEX);
  Serial.print("This memory address contains value: ");
  Serial.println(*my_var_pnt);

  // Experiment 4: You can use many pointers to access the same variable
  Serial.println();
  // You can use multiple pointers to access the same variable
  int *my_var_pnt2 = &my_var1;
  *my_var_pnt2 = 17;   // Change the value of my_var1 using its pointer
  // Access value using a pointer
  Serial.println("Access the new value of my_var using the new pointer.");
  Serial.print("*my_var_pnt2 points to memory address &my_var1: ");
  Serial.println((int) &my_var1, HEX);
  Serial.print("*my_var_pnt2 address contains value: ");
  Serial.println(*my_var_pnt2);

  Serial.println();
  // What about the pointer *my_var_pnt?
  Serial.print("*my_var_pnt address contains value: ");
  Serial.println(*my_var_pnt);

  // Experiment 5: pass a primitive to a function using a pointer or a reference
  Serial.println();
  // Call functions example.
  // First, pass a value using a pointer:
  my_function1(&my_var1);   // Pass object as a pointer
  Serial.print("*my_var_pnt address contains value: ");
  Serial.println(*my_var_pnt);
  Serial.println();
  
  // Second, pass a value using a reference:
  my_function2(my_var1);   // Pass object as a reference

  // Experiment 6: pass an object to a function via pointer or reference.
  TFT_eSPI tft = TFT_eSPI();  // Create an object to experiment with
  Serial.println();
  Serial.print("tft object address: ");
  Serial.println((int) &tft, HEX);
  my_function3(&tft);  // Pass object as a pointer
  my_function4(tft);   // Pass object as a reference
}

void loop() {
  // put your main code here, to run repeatedly:

}

void my_function1(int* local_pointer)
{
  Serial.print("In my_function1, the local_pointer address is: ");
  Serial.println((int) local_pointer, HEX);
  *local_pointer = 20;
}


void my_function2(int local_var)
{
  Serial.print("In my_function2, the local_var address is: ");
  Serial.println((int) &local_var, HEX);
}

void my_function3(TFT_eSPI* local_tft_pnt)
{
  Serial.print("In my_function3, the local_tft_pnt address is: ");
  //  Serial.println((int) &local_tft_pnt, HEX);
  Serial.println((int) local_tft_pnt, HEX);  // Get the address that this pointer is pointing to
}

void my_function4(TFT_eSPI local_tft)
{
  Serial.print("In my_function4, the local_tft address is: ");
  Serial.println((int) &local_tft, HEX);
}
