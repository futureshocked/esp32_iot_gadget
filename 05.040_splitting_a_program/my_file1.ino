void in_file1()
{
  Serial.println("Hello from File1");
  Serial.println(a_string);
}


// It is not possible to create a class in a seperate ino file.
// But, you can do so by creating a class in a .h and .cpp files.
//class Example_class {
//  void my_function()
//  {
//    Serial.println("Hello from example_class.my_function");
//  }
//}
