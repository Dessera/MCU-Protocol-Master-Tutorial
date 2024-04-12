#include <Arduino.h>

String receivingBufFromConsole; // Global variant，which is used in storing our input
void setup() {
  Serial.begin(115200);
  Serial.println("Program SetUp Success");
}

// the loop function runs over and over again forever
void loop() {
  // If the Serial can be used
  if(Serial.available())
  {
      receivingBufFromConsole = Serial.readString();
      Serial.println("I received the String from Console:> ");
      Serial.println(receivingBufFromConsole);
      Serial.println("Waiting for your next String...");
  }
// 	Following codes are commented, Bonus Question: what will the program behave if we compile the "else" 
// 	part code into the program? try by yourself
    
//  else
//  {
//      Serial.println("Current Serial has nothing to read! Program shell be terminated for 1ms");
//      delay(100);
///  }
}